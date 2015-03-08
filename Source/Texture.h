#pragma once
#include "Precompiled.h"

class Texture {
public:
    Texture(std::string fileName);
    ~Texture();

	GLuint GetTextureId() { return textureId; }

private:
	GLuint textureId;
	int textureWidth, textureHeight;
};