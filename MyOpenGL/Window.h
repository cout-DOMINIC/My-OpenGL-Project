#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


class Window
{
public:
	Window();
	Window(GLint with, GLint height);
	int InitialiseWindow();
	bool* GetKeys() { return keys; }
	GLFWwindow* mainWindow{ nullptr };
	GLint GetBufferWidth() { return bufferWidth;  }
	GLint GetBufferHeight() { return bufferHeight; }
	GLfloat PreventXoffsetMoving() { GLfloat theChange = xOffset; xOffset = 0.0f; return theChange; }
	GLfloat PreventYoffsetMoving() { GLfloat theChange = yOffset; yOffset = 0.0f; return theChange; }
	~Window() { glfwDestroyWindow(mainWindow); glfwTerminate(); }

private:
	// https://www.glfw.org/docs/3.0/group__keys.html
	bool keys[256]{ 0 };
	bool firstMouse = false;
	GLint width{ 0 }, height{ 0 }, bufferWidth{ 0 }, bufferHeight{ 0 };
	GLfloat lastX{ 0 }, lastY{ 0 }, xOffset{ 0 }, yOffset{ 0 };
	// https://www.glfw.org/docs/3.0/group__input.html
	static void GLFWkeyfun(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseCallback(GLFWwindow* window, double xPos, double yPos);
};

