#include "Camera.h"

Camera::Camera() { }

Camera::Camera(GLfloat cameraSpeed, GLfloat mouseSensitivity)
{
	this->cameraPos = glm::vec3(0.0f, 0.0f, 10.0f);
	// cameraDirection needs a positive or negative z-axis value
	// otherwiese cameraRight and cameraUp vector would not work properly
	this->cameraDirection = glm::vec3(0.0f, 0.0f, 1.0f);
	this->vectorUp = glm::vec3(0.0f, 1.0f, 0.0f);
	// yaw of 0.0f is pointing to the right
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
	this->cameraSpeed = cameraSpeed;
	this->mouseSensitivity = mouseSensitivity;
}

void Camera::ProcessKeyboardInput(bool* keys, GLfloat deltaTime)
{
	GLfloat velocity = cameraSpeed * deltaTime;

	if (keys[ GLFW_KEY_W] == GLFW_PRESS)
		cameraPos += cameraFront * velocity;
	else if (keys[GLFW_KEY_S] == GLFW_PRESS)
		cameraPos -= cameraFront * velocity;
	else if (keys[GLFW_KEY_A] == GLFW_PRESS)
		cameraPos -= cameraRight * velocity;
	else if (keys[GLFW_KEY_D] == GLFW_PRESS)
		cameraPos += cameraRight * velocity;
}

void Camera::UpdateMouse(GLfloat xOffset, GLfloat yOffset, GLfloat deltaTime)
{
	GLfloat velocity = mouseSensitivity * deltaTime;

	xOffset *= velocity;
	yOffset *= velocity;
	
	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f)
		pitch = 89.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraDirection.y = sin(glm::radians(pitch));
	cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	// important to normalize the vector!
	// to have one unit vector
	// (0, 0, 1)
	cameraFront = glm::normalize(cameraDirection);

	// (1, 0, 0)
	cameraRight = glm::normalize(glm::cross(cameraFront, vectorUp));
	// (0, 1, 0)
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}

// View Matrix
glm::mat4 Camera::ViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::~Camera() { }










