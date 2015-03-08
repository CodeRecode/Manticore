#pragma once
#include "Precompiled.h"

class ShaderProgram 
{
public:
	int program;

	ShaderProgram(std::string fileName) : program(0), fileName(fileName) { }

	void Initialize();
	void Bind();
	void UnBind();

private:
	std::string fileName;

	void Create();
	void Load(std::string fileName, GLenum type);
	void Link();
};