#pragma once

#include <GL/glew.h>
#include "Common.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLocation);
	bool LoadTextureA(); // with Alpha-Channel
	void UseTexture();
	~Texture();

private:
	GLuint textureID{ 0 };
	int width{ 0 }, height{ 0 }, bitDepth{ 0 };
	const char* fileLocation;
};

