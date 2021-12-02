#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(GLfloat cameraSpeed, GLfloat mouseSensitivity);
	void ProcessKeyboardInput(bool* keys, GLfloat deltaTime);
	void UpdateMouse(GLfloat xOffset, GLfloat yOffset, GLfloat deltaTime);
	glm::mat4 ViewMatrix();
	~Camera();

private:
	glm::vec3 cameraPos{ 0 };
	glm::vec3 cameraFront{ 0 };
	glm::vec3 cameraUp{ 0 };
	glm::vec3 cameraRight{ 0 };
	glm::vec3 vectorUp{ 0 };

	GLfloat yaw{ 0 }, pitch{ 0 };
	GLfloat cameraSpeed{ 0 }, mouseSensitivity{ 0 };
};

