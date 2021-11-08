#include "Test.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//int main()
//{
//	
//	const GLint WIDTH = 800, HEIGHT = 600;
//	ENGINE::TestWindow(WIDTH, HEIGHT);
//}

int ENGINE::TestWindow(GLint WIDTH, GLint HEIGHT)
{
	// Source: https://www.glfw.org/documentation.html 

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(WIDTH, HEIGHT, "My First Test Window!", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);




		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;

}
