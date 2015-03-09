#pragma once
#include "Precompiled.h"

class Texture;
class Mesh;
class ShaderProgram;

class Model 
{
public:
	Texture * texture;
	Mesh * mesh;

	Model(Texture * texture, Mesh * mesh) : texture(texture), mesh(mesh) { }

	void Draw(ShaderProgram * shader);
};