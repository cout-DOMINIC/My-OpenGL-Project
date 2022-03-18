#include "Window.h"

Window::Window() { }

Window::Window(GLint width, GLint height)
{
	this->width = width;
	this->height = height;
}

int Window::InitialiseWindow()
{
	if (!glfwInit()) { return -1; }

	// Setup GLFW window properties
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Independent Coursework 1", NULL, NULL);
	if (!mainWindow) { glfwTerminate(); return -1; }

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);

	//**********
	// Callbacks: Handle Key + Mouse Input
	glfwSetKeyCallback(mainWindow, GLFWkeyfun);
	glfwSetCursorPosCallback(mainWindow, MouseCallback);
	//**********

	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// vertical synchronization (vsync!)
	glfwSwapInterval(1);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);
}

// https://www.glfw.org/docs/3.0/group__input.html
void Window::GLFWkeyfun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key >= 0 && key < 256)
	{
		if (action == GLFW_PRESS)
			w->keys[key] = true;
		else if (action == GLFW_RELEASE)
			w->keys[key] = false;
	}
}

void Window::MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	Window* w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (w->firstMouse)
	{
		w->lastX = xPos;
		w->lastY = yPos;
		w->firstMouse = false;
	}

	w->xOffset = xPos - w->lastX;
	// prevent invert
	w->yOffset = w->lastY - yPos;

	w->lastX = xPos;
	w->lastY = yPos;
}