#pragma once
#include "Precompiled.h"

class Model {
public:
	Model(std::string filename);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> indices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec3> uvs;
};