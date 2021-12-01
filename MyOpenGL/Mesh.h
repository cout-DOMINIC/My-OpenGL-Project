#pragma once

#include <GL/glew.h>

// Mesh is important for model information
class Mesh
{
public:
	Mesh();
	void CreateMesh(GLfloat *vertices, GLuint *indices, GLuint numOfVertices, GLuint numOfIndices);
	void RenderMesh();
	~Mesh();

private:
	GLuint VAO{ 0 }, VBO{ 0 }, IBO{ 0 };
	GLsizei indexCount{ 0 };
};

