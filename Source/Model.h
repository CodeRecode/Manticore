#pragma once
#include "Precompiled.h"

class Texture;
class Mesh;
class ShaderProgram;

class Model 
{
public:
	Model(Texture * texture, Mesh * mesh) : texture(texture), mesh(mesh) { }

	void Draw(ShaderProgram * shader);

private:
	Texture * texture;
	Mesh * mesh;
};