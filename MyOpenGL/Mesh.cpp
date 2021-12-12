#include <stdio.h>

#include "Mesh.h"

Mesh::Mesh() { }

void Mesh::CreateMesh(GLfloat* vertices, GLuint* indices, GLuint numOfVertices, GLuint numOfIndices)
{
	indexCount = numOfIndices;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	// indices[] = [4 * 3] * numOfIndices = (4 * 3)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * numOfIndices, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// indices[] = [4 * 3] * numOfIndices = (4 * 3)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * numOfVertices, vertices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
	// Altered function b/s of Texture
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices) * 5, nullptr);
	//

	glEnableVertexAttribArray(0);

	// Texture
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices) * 5, (void*)(sizeof(vertices) * 3));
	glEnableVertexAttribArray(1);
	//

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
	glBindVertexArray(VAO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// number of indexCount gets pasted in CreateMesh function
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh() { }
