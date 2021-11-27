#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"

// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
//Bogenmaﬂ
const GLfloat toRadians{ 3.14159265f / 180.0f };

// a list for all mesh objects
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

GLfloat curAngle{0.0f};

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triMaxoffset2 = -0.7f;
float triIncrement = 0.01f;

// Creating Vertex Shader itself
static const char* VertexShader = "Shaders/shader.vertex";

// Creating Fragment Shader itself
static const char* FragmentShader = "Shaders/shader.fragment";

void CreateObjects()
{

	GLuint indices[4 * 3] = {
		0, 1, 2,
		
		1, 3, 2,
		
		0, 1, 3,
		
		0, 3, 2
	};


	// OpenGL is in C, so vectors wont work
	GLfloat vertices[4 * 3] =
	{
		-1.0f, -1.0f, 0.0f,
		// this one is going into the background!
		 0.0f, -1.0f, 1.0f,

		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f
	};



	GLuint indicesSquare[12 * 3] = {
	// Front
	0, 1, 2,
	1, 3, 2,
	// rechte Seite
	1, 3, 5,
	3, 5, 7,
	// Back
	4, 6, 5,
	6, 7, 5,
	// Left Side
	2, 4, 6,
	0, 2, 4,
	// Top
	2, 3, 7,
	2, 7, 6,
	// Bottom
	1, 4, 5,
	0, 1, 4,
	};


	// Square
	GLfloat verticesSquare[8 * 3] =
	{
		// links unten
		-1.0f, -1.0f, 0.0f,
		// rechts unten
		 1.0f, -1.0f, 0.0f,
		// links oben
		-1.0f, 1.0f, 0.0f,
		// rechts oben
		1.0f, 1.0f, 0.0f,


		// links unten hinten
		-1.0f, -1.0f, 1.0f,
		// rechts unten hinten
		1.0f, -1.0f, 1.0f,
		// links oben hinten
		-1.0f, 1.0f, 1.0f,
		// rechts oben hinten
		1.0f, 1.0f, 1.0f,

	};


	GLuint indicesPyramid[6 * 3] = {
		// Front
		0, 1, 2,
		// rechte Seite
		1, 3, 2,
		// Back
		3,4,2,
		// Left Side
		4, 0, 2,
		// Bottom
		0,1,4,
		1,3,4
	};


	// Square
	GLfloat verticesPyramid[5 * 3] =
	{
		// links unten
		-1.0f, -1.0f, 0.0f,
		// rechts unten
		 1.0f, -1.0f, 0.0f,
		 // links hinten
		 -1.0f, -1.0f, 1.0f,
		 // rechts hinten
		 1.0f, -1.0f, 1.0f,
		 // Spitze
		 0.0f, 1.0f, 0.5f

	};



	// Creating new triangle mesh objects

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, (4 * 3), (4 * 3));
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, (4 * 3), (4 * 3));
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(vertices, indices, (4 * 3), (4 * 3));
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(verticesSquare, indicesSquare, (8 * 3), (12 * 3));
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(verticesPyramid, indicesPyramid, (5 * 3), (6 * 3));
	meshList.push_back(obj5);
}

void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(VertexShader, FragmentShader);
	shaderList.push_back(shader1);
}

int main()
{
	// Initialise GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialisation failed!\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("GLFW window creation failed!");
		glfwTerminate();
		return 1;
	}

	// Get Buffer Size information
	int bufferWidth, bufferHeight;
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//
	glfwSwapInterval(1);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialisation failed!\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	CreateObjects();
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;

	// Projectionmatrix itself
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		if (direction)
		{
			triOffset += triIncrement;
		}
		else if(!direction) {
			triOffset -= triIncrement;
		}

		if (triOffset > triMaxoffset)
		{
			direction = false;
		}

		if (triOffset < triMaxoffset2)
		{
			direction = true;
		}

		curAngle += 0.5f;

		if (curAngle >= 360)
		{
			curAngle -= 360;
		}

		glUniform1f(uniformModel, triOffset);

		// Clear window
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();

		// initialised 4 x 4 matrix
		glm::mat4 model{1.0f};

		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
		// model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		// creating an identity matrix and clearing out the model
		// the translates and scales are not there anymore
		// means it's possible to create another model with it's own translate and scale
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-triOffset, 1.0f, -2.5f));
		// model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		// creating an identity matrix and clearing out the model
		// the translates and scales are not there anymore
		// means it's possible to create another model with it's own translate and scale
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.0f, -1.0f, -4.5f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[2]->RenderMesh();



		// Square
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.4f, -1.0f, -6.0f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(-1.0f, -1.0f, 1.0f));
		model = glm::scale(model, glm::vec3(0.3f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[3]->RenderMesh();


		// Pyramid
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.1f, -4.0f));
		model = glm::rotate(model, curAngle * toRadians, glm::vec3(-1.0f, -1.0f, -1.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();


		glUseProgram(0);
		glfwSwapBuffers(mainWindow);
	}

	return 0;
}