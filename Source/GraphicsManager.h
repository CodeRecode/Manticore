#pragma once
#include "IManager.h"
#include "Model.h"
#include "Shader.h"

class Core;

class GraphicsManager : public IManager {
public:
    GraphicsManager(Core * core);
    void Update(double frameTime) override;

	ShaderProgram sp;
	Model * m;
};