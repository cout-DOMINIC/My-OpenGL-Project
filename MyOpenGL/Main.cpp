#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Window dimensions
const GLint WIDTH = 800, HEIGHT = 600;
//Bogenmaß
const GLfloat toRadians{ 3.14159265f / 180.0f };

// OpenGL unsigned int
GLuint VBO, VAO, shader, uniformModel, uniformProjection;
// Index Buffer Object
GLuint IBO;

GLsizei n{1};
GLfloat curAngle{0.0f};

GLfloat scaleSize{0.0f};

bool direction = true;
float triOffset = 0.0f;
float triMaxoffset = 0.7f;
float triMaxoffset2 = -0.7f;
float triIncrement = 0.01f;

GLboolean sizreDirection = true;
GLfloat curSize{ 0.4f };
GLfloat maxSize{ 0.8f };
GLfloat minSize{ 0.1f };

// Creating Vertex Shader itself
static const char* VertexShader = "								\n\
#version 330													\n\
layout (location = 0) in vec3 pos;								\n\
\n\
\n\
out vec4 vertexColor;\n\
\n\
																\n\
uniform mat4 model;											    \n\
\n\
uniform mat4 projection;											    \n\
\n\
																\n\
void main()														\n\
{   // die ersten 3 Werte in Vec4 sind die drei Werte aus Vec3  \n\
	// Das funktioniert, WENN wir glm::scale aufrufen und die Größe festlegen	\n\
	gl_Position = projection * model * vec4(pos, 1.0);										\n\
	vertexColor = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);							\n\ \n\
}";

// Creating Fragment Shader itself
static const char* FragmentShader = "							\n\
#version 330													\n\
out vec4 color;													\n\
																\n\
\n\
in vec4 vertexColor;\n\
\n\
uniform vec4 u_Color;											\n\
																\n\
void main()														\n\
{																\n\
	 // color = u_Color;                                         \n\
	 color = vertexColor;											\n\
}";

void CreateTriangle()
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

	// (GLsizei; amount of arrays I'd like to create, GLuint *arrays; where you want to store the ID of the array);
	glGenVertexArrays(n, &VAO);
	// (GLuint array; specifies the name/ID of the vertex array to bind);
	glBindVertexArray(VAO);
	

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (4 * 3) * sizeof(float), indices, GL_STATIC_DRAW);


	// Creating a Buffer Object / an ID (GLsizei; number of buffers I'd like to create, GLuint *buffers; where you want to store the ID of the buffer);
	glGenBuffers(n, &VBO);
	// (GLenum target; specifies which buffer we'd like to bind, GLuint buffer; specifies the name/ID of the buffer to bind);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Erstellt und initialisiert den Datenspeicher eines Bufferobjekts
	// (GLenum target; specifies the target to which the buffer object is bound for glBufferData, GLsizeiptr size; the size of the data passing in (Arrays size), 
	// const GLvoid* data; the array itself, GLenum usage; expected usage pattern of the data store)
	glBufferData(GL_ARRAY_BUFFER, (4 * 3) * sizeof(float), vertices, GL_STATIC_DRAW);

	// (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	glEnableVertexAttribArray(0);

	// Unbinding the Buffer and Vertex Array after they have been created
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//void CreateTriangle()
//{
//	GLfloat vertices[] = {
//		-1.0f, -1.0f, 0.0f,
//		1.0f, -1.0f, 0.0f,
//		0.0f, 1.0f, 0.0f
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glBindVertexArray(VAO);
//
//	glGenBuffers(1, &VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	glBindVertexArray(0);
//}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	// create the individual shader
	GLuint theShader = glCreateShader(shaderType);

	// create an array; pass in a pointer to the first element of an array
	// this is where we actually store the code itself
	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	// to hold the length of the code
	GLint codeLength[1];
	// strlen return the length of the code / string
	codeLength[0] = strlen(shaderCode);

	// (handle of the shader, the number of elements in the string, an array of pointers to strings the source code to be loaded into the shader, array of string lengths)
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);


	// Errir handling again
	GLint result{ 0 };
	GLchar eLog[1024]{ 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetShaderInfoLog(theShader, 1024, NULL, eLog);
		fprintf(stderr, "Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	// attaches a shader object to prgram object itself
	glAttachShader(theProgram, theShader);
}


void CompileShaders()
{
	// creating the program itself
	shader = glCreateProgram();
	// if shader is not available
	if (shader == GL_FALSE)
	{
		std::cout << "Failed to create shader\n";
		return;
	}
	// adding both shader to the program! Vertex and Fragment are both mandatory
	AddShader(shader, VertexShader, GL_VERTEX_SHADER);
	AddShader(shader, FragmentShader, GL_FRAGMENT_SHADER);

	// Error handling
	// we need to link and validate the program

	GLint result{ 0 };
	// a place to log the error; how many characters 1024
	GLchar eLog[1024]{ 0 };

	// with this Code, our function is done! But, we need to make sure that everything works fine
	glLinkProgram(shader);

	// to making sure that it linked properly 
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}
	// to making sure that the validation went properly
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (result == GL_FALSE)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}

	uniformModel = glGetUniformLocation(shader, "model");




	uniformProjection = glGetUniformLocation(shader, "projection");



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

	CreateTriangle();
	CompileShaders();


	// Projectionmatrix itself
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);





	//glUseProgram(shader);
	int location = glGetUniformLocation(shader, "u_Color");
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	//uniformXMove = glGetUniformLocation(shader, "u_xMove");
	// glUniform1f(uniformXMove, 1.0f);
	
	//float xMove = 0.0f;
	//float incrementMove = 0.0f;

	float red = 0.0f;
	float increment = 0.05f;

	// Loop until window closed
	while (!glfwWindowShouldClose(mainWindow))
	{
		// Get + Handle user input events
		glfwPollEvents();

		glUniform1f(uniformModel, triOffset);

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


		//if (curAngle >= 360)
		//{
		//	curAngle -= 360;
		//}

		if (direction)
		{
			curSize += 0.001f;
		}
		else {
			curSize -= 0.001f;
		}

		if (curSize >= maxSize || curSize <= minSize)
		{
			sizreDirection = !sizreDirection;
		}

		glUniform1f(uniformModel, triOffset);


		// Clear window
		glClearColor(0.0f, 1.0f, 1.0f, 1.0f);




		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		




		glUniform4f(location, red, 0.1f, 0.0f, 1.0f);
		if (red > 1.0f)
			increment = -0.05f;
		else if (red < 0.0f)
			increment = 0.05f;
		red += increment;

		glBindVertexArray(VAO);





		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);






		//(What we would like to render, starting point of index (makes sense to start always from 0), how many vertices one index has (x,y,z = 3))
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		glUseProgram(shader);

	
		glm::mat4 model{1.0f};

		model = glm::translate(model, glm::vec3(triOffset, 0.0f, -2.5f));
		// model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
		
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));



		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));


		glfwSwapBuffers(mainWindow);
	}

	return 0;
}