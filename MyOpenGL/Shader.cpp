#include "Shader.h"

Shader::Shader() { }

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation);

	if (fileStream.is_open())
	{
		while (!fileStream.eof())
		{
			std::string line = "";
			std::getline(fileStream, line);
			content.append(line + "\n");
		}
		fileStream.close();
	}
	else {
		printf("Failed to read %s! File does not exist.", fileLocation);
		return "";
	}
	return content;
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
	AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	glLinkProgram(shaderID);
	glValidateProgram(shaderID);
	
	uniformModel = glGetUniformLocation(shaderID, "model");
	uniformProjection = glGetUniformLocation(shaderID, "projection");
	uniformView = glGetUniformLocation(shaderID, "view");
	uniformAmbientColor = glGetUniformLocation(shaderID, "directionalLight.color");
	uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
}

void Shader::CreateShaderCode(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	// convert string into a C-style string (const char*)
	const char* vertexCode = vertexString.c_str();
	const char* fragmentCode = fragmentString.c_str();

	CompileShader(vertexCode, fragmentCode);
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);
	glAttachShader(theProgram, theShader);
}

Shader::~Shader() { }