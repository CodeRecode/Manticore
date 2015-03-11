#pragma once
#include "Precompiled.h"

class Mesh {
public:
	Mesh();
	
	std::vector<glm::vec4> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> texCoords;
	std::vector<int> indices;

	void LoadFromObj(std::string fileName);
	void GenerateVao();
	void Draw();

private:
	GLuint vao;
	int triangleCount;
};