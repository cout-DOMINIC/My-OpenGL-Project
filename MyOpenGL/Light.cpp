#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = intensity;
}

void Light::CreateLight(GLfloat ambientIntensityL, GLfloat ambientColorL)
{
	glUniform3f(ambientColorL, color.x, color.y, color.z);
	glUniform1f(ambientIntensityL, ambientIntensity);
}

Light::~Light() { }