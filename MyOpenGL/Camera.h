#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange, GLfloat deltaTime);

	glm::mat4 calculateViewMatrix();

	~Camera();

private:
	glm::vec3 position{ 0 };
	glm::vec3 front{ 0 };
	glm::vec3 up{ 0 };
	glm::vec3 right{ 0 };
	glm::vec3 worldUp{ 0 };

	GLfloat yaw{ 0 };
	GLfloat pitch{ 0 };

	GLfloat moveSpeed{ 0 };
	GLfloat turnSpeed{ 0 };

	void update();
};

