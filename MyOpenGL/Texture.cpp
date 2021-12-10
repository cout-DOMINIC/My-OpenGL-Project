#include "Texture.h"

Texture::Texture()
{
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->bitDepth = 0;
	this->fileLocation = nullptr;
}

Texture::Texture(char* fileLocation)
{
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->bitDepth = 0;
	this->fileLocation = fileLocation;
}

void Texture::LoadTexture()
{
	//unsigned char* textureData = stbi_load(fileLocation, &width, &height, &bitDepth, 0);
	//if (!textureData)
	//{
	//	printf("Failed to find: %s\n", fileLocation);
	//	return;
	//}
	//
	//glGenTextures(1, &textureID);
	//glBindTexture(GL_TEXTURE_2D, textureID);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	//glGenerateMipmap(GL_TEXTURE_2D);

	//glBindTexture(GL_TEXTURE_2D, 0);

	//stbi_image_free(textureData);
}

void Texture::UseTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::ClearTexture()
{
	glDeleteTextures(1, &textureID);
	this->textureID = 0;
	this->width = 0;
	this->height = 0;
	this->bitDepth = 0;
	this->fileLocation = nullptr;
}

Texture::~Texture()
{
	ClearTexture();
}