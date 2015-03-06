#pragma once
#include "glm.hpp"

class Collider {
public:
    Collider(glm::vec3 & position) : position(position), velocity(0), isStatic(false) { }
    virtual ~Collider() { }
    bool isStatic;
    float boundingRadius;
	glm::vec3 & position, velocity;
};

class BoxCollider {    
public:
    float height, length, width;
};

class SphereCollider {
public:
    float radius;
};