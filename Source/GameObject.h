#pragma once
#include "Transform.h"
#include "Texture.h"
#include "Collider.h"

class GameObject {
public:
    GameObject() : texture(nullptr), collider(nullptr) { };

    Transform transform;
    Texture *texture;
    Collider *collider;
};