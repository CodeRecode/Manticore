#pragma once
#include "IManager.h"
#include "Model.h"
#include "Shader.h"

class Core;

class GraphicsManager : public IManager 
{
public:
	GraphicsManager(Core * core);

	void Init();
	void Update(double frameTime) override;
	void PrintGLError();

private:
	ShaderProgram basicShader;
	Model * m;
};