#include <iostream>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"


// covers range of ascii codes
bool keys[1024];
// Window dimensions
const GLint WIDTH = 1024, HEIGHT = 768;
// Bogenmaß (für Winkel)
const GLfloat toRadians{ 3.14159265f / 180.0f };

Window* mainWindow;
// lists for all mesh and shader objects
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

Camera* camera;
GLfloat deltaTime{ 0.0f };
GLfloat lastFrame{ 0.0f };

// Creating Vertex Shader itself
/*static*/ const char* VertexShader = "Shaders/shader.vertex";

// Creating Fragment Shader itself
/*static*/ const char* FragmentShader = "Shaders/shader.fragment";

void CreateObjects()
{
	GLuint indicesTriangle[4 * 3] = {
		0, 1, 2,
		1, 3, 2,
		0, 1, 3,
		0, 3, 2
	};

	GLfloat verticesTriangle[4 * 3] =
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
		3, 4, 2,
		// Left Side
		4, 0, 2,
		// Bottom
		0, 1, 4,
		1, 3, 4
	};

	GLfloat verticesPyramid[5 * 3] =
	{
		// left down
		-1.0f, -1.0f, 0.0f,
		// right down
		 1.0f, -1.0f, 0.0f,
		// left back
	    -1.0f, -1.0f, 1.0f,
		// right back
		 1.0f, -1.0f, 1.0f,
		// peak
		 0.0f, 1.0f, 0.5f
	};

	// Creating new triangle mesh objects
	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(verticesTriangle, indicesTriangle, (4 * 3), (4 * 3));
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
	shader1->CreateShaderCode(VertexShader, FragmentShader);
	shaderList.push_back(shader1);
}

int main()
{
	mainWindow = new Window(1060, 600);
	mainWindow->InitialiseWindow();
	// Camera speed, Mouse sensitivity
	camera = new Camera(10.0f, 6.0f);

	CreateObjects();
	CreateShaders();

	GLfloat curAngle{ 0.0f };
	GLuint uniformProjection{0};
	GLuint uniformModel{0};
	GLuint uniformView{ 0 };

	// Projectionmatrix itself
	glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mainWindow->GetBufferWidth()) / static_cast<GLfloat>(mainWindow->GetBufferHeight()), 0.1f, 100.0f);

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow->mainWindow))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		camera->ProcessKeyboardInput(mainWindow->GetKeys(), deltaTime);
		camera->UpdateMouse(mainWindow->PreventXoffsetMoving(), mainWindow->PreventYoffsetMoving(), deltaTime);

		// Clear window
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i{0}; i < shaderList.size(); ++i)
		{
			shaderList[i]->UseShaderProgram();
			uniformModel = shaderList[i]->GetUniformModel();
			uniformProjection = shaderList[i]->GetUniformProjection();
			uniformView = shaderList[i]->GetUniformView();
		}

		// initialised 4 x 4 matrix
		glm::mat4 triangle{1.0f};
		glm::mat4 square{1.0f};
		glm::mat4 pyramid{1.0f};

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera->ViewMatrix()));
		curAngle += 0.3f;

		// Triangle
		triangle = glm::translate(triangle, glm::vec3(-2.0f, 0.0f, -4.5f));
		triangle = glm::rotate(triangle, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		triangle = glm::scale(triangle, glm::vec3(0.3f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(triangle));
		meshList[0]->RenderMesh();

		// Square
		square = glm::translate(square, glm::vec3(2.4f, 0.0f, -6.0f));
		square = glm::rotate(square, curAngle * toRadians, glm::vec3(-1.0f, -1.0f, 1.0f));
		square = glm::scale(square, glm::vec3(0.3f, 0.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(square));
		meshList[1]->RenderMesh();

		// Pyramid
		pyramid = glm::translate(pyramid, glm::vec3(0.0f, -0.5f, -4.0f));
		pyramid = glm::rotate(pyramid, curAngle * toRadians, glm::vec3(-1.0f, -1.0f, -1.0f));
		pyramid = glm::scale(pyramid, glm::vec3(0.5f, 0.5f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(pyramid));
		meshList[2]->RenderMesh();

		glUseProgram(0);

		// Swap front and back buffers
		glfwSwapBuffers(mainWindow->mainWindow);
		// poll events (keys pressed and / or released | mouse moved or not)
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}