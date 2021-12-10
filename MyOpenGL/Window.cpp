#include "Window.h"


Window::Window() { }

Window::Window(GLint width, GLint height)
{
	this->width = width;
	this->height = height;
}

int Window::InitialiseWindow()
{
	// Initialise GLFW
	if (!glfwInit()) { return -1; }

	// Setup GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Core Profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Allow Forward Compatbility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(width, height, "Independent Coursework 1", NULL, NULL);
	if (!mainWindow) { glfwTerminate(); return -1; }

	// Get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	//**********
	// Callbacks: Handle Key + Mouse Input
	glfwSetKeyCallback(mainWindow, GLFWkeyfun);
	glfwSetCursorPosCallback(mainWindow, MouseCallback);
	//**********

	// Mauszeiger wird, sobald die Anwendung den Fokus, ausgeblendet und platziert sich in der Mitte des Fensters
	// Verliert die Anwendung den Fokus oder wird beendet, wird der Mauszeiger wieder eingeblendet
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// vertical synchronization (vsync!)
	// 1 is the minimum number of screen updates to wait for until the buffers are swapped
	// not necessary but can be useful
	glfwSwapInterval(1);

	// Allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// Setup Viewport size
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