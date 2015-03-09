#include "Mesh.h"

Mesh::Mesh() : vao(0), triangleCount(0)
{
	LoadFromObj("./Models/cube.obj");
}

void Mesh::LoadFromObj(std::string fileName)
{
	std::vector<std::tuple<int, int, int>> vertexData;
	std::vector<glm::vec3> objPositions, objNormals;
	std::vector<glm::vec2> objTexCoords;

	std::ifstream modelFile(fileName);
	std::string type, path, line, face;
	char dummy;
	float x, y, z;

	// Read .obj file
	while (std::getline(modelFile, line))
	{
		if (line.length() == 0)
			continue;

		std::istringstream inputss(line);
		inputss >> type;

		if (type == "v")
		{
			inputss >> x >> y >> z;
			objPositions.push_back(glm::vec3(x, y, z));
		}
		else if (type == "vn")
		{
			inputss >> x >> y >> z;
			objNormals.push_back(glm::vec3(x, y, z));
		}
		else if (type == "vt")
		{
			inputss >> x >> y >> z;
			objTexCoords.push_back(glm::vec2(x, y));
		}
		else if (type == "f") // v/t/n
		{
			for (int i = 0; i < 3; i++)
			{
				inputss >> face;
				std::istringstream indexss(face);
				indexss >> x >> dummy >> y >> dummy >> z;
				vertexData.push_back(std::make_tuple<int, int, int>(x - 1, y - 1, z - 1));
			}
		}
	}

	std::map<std::tuple<int, int, int>, int> vertexMap;
	int index = 0;

	// Generate index data
	for (int i = 0; i < vertexData.size(); ++i)
	{
		std::tuple<int, int, int> vertex = vertexData[i];
		if (vertexMap.count(vertex) == 0)
		{
			vertexMap[vertexData[i]] == index;

			positions.push_back(objPositions[std::get<0>(vertex)]);
			texCoords.push_back(objTexCoords[std::get<1>(vertex)]);
			normals.push_back(objNormals[std::get<2>(vertex)]);
			indices.push_back(index);

			index++;
		}
		else
		{
			indices.push_back(vertexMap[vertexData[i]]);
		}
	}

	GenerateVao();
}

void Mesh::GenerateVao()
{
	GLuint vboVertices, vboNormals, vboTexCoords, vboIndices;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Vertices
	glGenBuffers(1, &vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Normals
	glGenBuffers(1, &vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Texture Coordinates
	glGenBuffers(1, &vboTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, vboTexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Indices
	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	triangleCount = indices.size();
}

void Mesh::Draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, triangleCount, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}