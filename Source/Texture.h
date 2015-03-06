#pragma once
#include "Precompiled.h"

class Texture {
public:
    Texture(std::string fileName);
    ~Texture();

    void Draw();

    float scale;

private:
    unsigned int textureId;
};