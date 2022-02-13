#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
	Shader();
	std::string ReadFile(const char* fileLocation);
	void CreateShaderCode(const char* vertexLocation, const char* fragmentLocation);
	void UseShaderProgram() { glUseProgram(shaderID); }
	GLuint GetUniformProjection() { return uniformProjection; }
	GLuint GetUniformModel() { return uniformModel; }
	GLuint GetUniformView() { return uniformView; }
	GLuint GetAmbientIntensityLocation() { return uniformAmbientIntensity; };
	GLuint GetAmbientColorLocation() { return uniformAmbientColor; };
	~Shader();

private:
	GLuint shaderID{ 0 }, uniformProjection{ 0 }, uniformModel{ 0 }, uniformView{ 0 }, uniformAmbientIntensity{ 0 }, uniformAmbientColor{ 0 };
	void CompileShader(const char* vertexCode, const char* fragmentCode);
	void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};

