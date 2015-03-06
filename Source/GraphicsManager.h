#pragma once
#include "IManager.h"

class Core;

class GraphicsManager : public IManager {
public:
    GraphicsManager(Core * core);
    void Update(double frameTime) override;
};