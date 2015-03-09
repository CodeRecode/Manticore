#pragma once
#include "Precompiled.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string fileName) : program(0), fileName(fileName) { }

	void Initialize();
	void Bind();
	void UnBind();
	int GetShaderProgram() { return program; }

private:
	int program;
	std::string fileName;

	void Create();
	void Load(std::string fileName, GLenum type);
	void Link();
};