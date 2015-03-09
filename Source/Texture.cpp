#include "Texture.h"

Texture::Texture(std::string fileName)
{
	glGenTextures(1, &textureId);

	// Load and convert the image with DevIL
	ILuint imageID;
	ilGenImages(1, &imageID);
	ilBindImage(imageID);
	ilLoadImage(fileName.c_str());
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	iluFlipImage();

	textureWidth = ilGetInteger(IL_IMAGE_WIDTH);
	textureHeight = ilGetInteger(IL_IMAGE_HEIGHT);

	// Bind the texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), textureWidth, textureHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
	ilDeleteImage(imageID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, NULL);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}