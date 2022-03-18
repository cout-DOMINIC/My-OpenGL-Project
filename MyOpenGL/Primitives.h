#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Primitives
{
public:
	Primitives();
	~Primitives();

	GLuint indicesTriangle[4 * 3] = {
		0, 1, 2,
		1, 3, 2,
		0, 1, 3,
		0, 3, 2
	};

	GLfloat verticesTriangle[4 * 5] =
	{
		// X	 Y	   Z		 U		 V
		-1.0f, -1.0f, 0.0f,		0.0f,	0.0f,
		// this one is going into the background!
		0.0f, -1.0f, 1.0f,		1.0f,	0.0f,
		1.0f, -1.0f, 0.0f,		2.0f,	0.0f,
		0.0f,  1.0f, 0.0f,		1.0f,	2.0f,
	};

	GLuint indicesSquare[12 * 3] = {
		// Front
		0, 1, 2,
		1, 3, 2,
		// Right
		1, 3, 5,
		3, 5, 7,
		// Back
		4, 6, 5,
		6, 7, 5,
		// Left
		2, 4, 6,
		0, 2, 4,
		// Top
		2, 3, 7,
		2, 7, 6,
		// Bottom
		1, 4, 5,
		0, 1, 4,
	};

	GLfloat verticesSquare[8 * 5] =
	{
		// X	 Y	   Z	     U		 V
		-1.0f, -1.0f, 0.0f,		0.0f,	0.0f,
		// down right
		1.0f, -1.0f, 0.0f,		1.0f,	0.0f,
		// top left
		-1.0f, 1.0f, 0.0f,		0.0f,	2.0f,
		// top right
		1.0f, 1.0f, 0.0f,		1.0f,	1.0f,

		// back down left
		-1.0f, -1.0f, 1.0f,		1.0f,	1.0f,
		// back down right
		1.0f, -1.0f, 1.0f,		2.0f,	0.0f,
		// back top left
		-1.0f, 1.0f, 1.0f,		0.0f,	1.0f,
		// back up right
		1.0f, 1.0f, 1.0f,		2.0f,	2.0f
	};

	GLuint indicesPyramid[6 * 3] = {
		// Front
		0, 1, 2,
		// Right
		1, 3, 2,
		// Back
		3, 4, 2,
		// Left
		4, 0, 2,
		// Bottom
		0, 1, 4,
		1, 3, 4
	};

	GLfloat verticesPyramid[5 * 5] =
	{
		// X	 Y	   Z		 U		 V
		// down left
		-1.0f, -1.0f, 0.0f,		0.0f,	0.0f,
		// down right
		1.0f, -1.0f, 0.0f,		1.0f,	0.0f,
		// back left
		-1.0f, -1.0f, 1.0f,		1.0f,	1.0f,
		// back right
		1.0f, -1.0f, 1.0f,		2.0f,	0.0f,
		// peak
		0.0f, 1.0f, 0.5f,		0.5f,	1.0f,
	};

	GLuint indicesFloor[2 * 3] =
	{
		0, 1, 2,
		1, 3, 2,
	};

	GLfloat verticesFloor[4 * 5] =
	{
		// 10 to make floor larger
		// X     Y	   Z		 U		 V
		-10.0f, 0.0f, -10.0f,	0.0f,	0.0f,
		10.0f, 0.0f, -10.0f,	10.0f,	0.0f,
		-10.0f,	0.0f, 10.0f,	0.0f,	10.0f,
		10.0f, 0.0f, 10.0f,		10.0f,	10.0f,
	};

	GLuint indicesHouse[12 * 3] = {
		// Front
		0, 1, 2,
		1, 3, 2,
		// right
		1, 3, 5,
		3, 5, 7,
		// Back
		4, 6, 5,
		6, 7, 5,
		// Left
		2, 4, 6,
		0, 2, 4,
		// Top
		2, 3, 7,
		2, 7, 6,
		// Bottom
		1, 4, 5,
		0, 1, 4,
	};

	GLfloat verticesHouse[8 * 5] =
	{
		// X	 Y	   Z		 U		 V
		// down left
		-1.0f, -1.0f, 0.0f,		0.0f,	0.0f,
		// down right
		1.0f, -1.0f, 0.0f,		3.0f,	0.0f,
		// up left
		-1.0f, 1.0f, 0.0f,		0.0f,	4.0f,
		// up right
		1.0f, 1.0f, 0.0f,		3.0f,	3.0f,

		// back down left
		-1.0f, -1.0f, 1.0f,		3.0f,	3.0f,
		// back down right
		1.0f, -1.0f, 1.0f,		4.0f,	0.0f,
		// back up left
		-1.0f, 1.0f, 1.0f,		0.0f,	3.0f,
		// back up right
		1.0f, 1.0f, 1.0f,		4.0f,	4.0f
	};
};