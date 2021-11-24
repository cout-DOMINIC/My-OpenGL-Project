#pragma once

#include <GL/glew.h>

// Mesh is important for model information
class Mesh
{
public:
	Mesh();

	void CreateMesh(GLfloat *vertices, GLuint *indices, GLuint numOfVertices, GLuint numOfIndices);
	void RenderMesh();
	void ClearMesh();

	~Mesh();

private:
	GLuint VAO, VBO, IBO;
	GLsizei indexCount;
};

