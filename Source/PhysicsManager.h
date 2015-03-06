#pragma once
#include "IManager.h"

class Core;

class PhysicsManager : public IManager {
public:
    PhysicsManager(Core *core);
    void Update(double frameTime) override;
};