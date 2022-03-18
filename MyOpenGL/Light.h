#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity);
	void CreateLight(GLfloat ambientIntensityL, GLfloat ambientColorL);
	~Light();

private:
	glm::vec3 color;
	GLfloat ambientIntensity{ 0 };
};

