#pragma once
#include "Precompiled.h"
#include "IManager.h"
#include "GameObject.h"

class Core;

class LuaManager : public IManager {
private:
    lua_State *L;

public:
    LuaManager(Core *core);
    void Update(double frameTime) override;
    
	GameObject* CreateGameObject();

    GameObject* SetPosition(GameObject *obj, float x, float y, float z);
    GameObject* SetRotation(GameObject *obj, float x, float y, float z);
    GameObject* SetScale(GameObject *obj, float x, float y, float z);
    
    GameObject* AddCollider(GameObject *obj);
    GameObject* SetVelocity(GameObject *obj, float x, float y, float z);

    GameObject* SetTexture(GameObject *obj, std::string textureName);

    void AddGameObject(GameObject *obj);
};