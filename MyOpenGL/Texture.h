#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);

	bool LoadTexture();
	bool LoadTextureA(); // Alpha-Channel

	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;
	int width{ 0 }, height{ 0 }, bitDepth{ 0 };

	const char* fileLocation;
};

