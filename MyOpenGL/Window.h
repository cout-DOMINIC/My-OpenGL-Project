#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWith, GLint windowHeight);

	int Initialise();

	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }

	bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

	bool* getKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	~Window();
private:
	GLFWwindow* mainWindow{nullptr};
	GLint width{ 0 }, height{ 0 }, bufferWidth{ 0 }, bufferHeight{ 0 };

	bool keys[1024]{ 0 };

	GLfloat lastX{ 0 };
	GLfloat lastY{ 0 };
	GLfloat xChange{ 0 };
	GLfloat yChange{ 0 };
	bool mouseFirstMoved = false;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
};

