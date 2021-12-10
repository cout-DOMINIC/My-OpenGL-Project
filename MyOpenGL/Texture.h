#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(char* fileLocation);

	void LoadTexture();
	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID{ 0 };
	int width{ 0 }, height{ 0 }, bitDepth{ 0 };

	char* fileLocation;
};

