#pragma once
#include "glm.hpp"

class Transform {
public:
    glm::vec3 translation, scale, rotation;

    Transform() : translation(), scale(1, 1, 1), rotation() { };
};