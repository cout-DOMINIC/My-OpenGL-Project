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
		//	  X		 Y	   Z			 U		 V
		-1.0f, -1.0f, 0.0f,			0.0f,	0.0f,
		// this one is going into the background!
		0.0f, -1.0f, 1.0f,			1.0f,	0.0f,
		1.0f, -1.0f, 0.0f,			2.0f,	0.0f,
		0.0f,  1.0f, 0.0f,			1.0f,	2.0f,
	};


};

