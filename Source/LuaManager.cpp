#include "LuaManager.h"
#include "Core.h"
#include "glm.hpp"

LuaManager::LuaManager(Core *core) : IManager(core) {
    L = luaL_newstate();    
    luaL_openlibs(L);


    luabridge::getGlobalNamespace(L)
		.beginClass<glm::vec3>("vec3")
		.addData("x", &glm::vec3::x)
		.addData("y", &glm::vec3::y)
		.addData("z", &glm::vec3::z)
        .endClass();
    
    luabridge::getGlobalNamespace(L)
        .beginClass<GameObject>("GameObject")
        .endClass();

    luabridge::getGlobalNamespace(L)
        .beginClass<LuaManager>("LuaManager")
        .addFunction("SetPosition", &LuaManager::SetPosition)
        .addFunction("SetRotation", &LuaManager::SetRotation)
        .addFunction("SetScale", &LuaManager::SetScale)
        .addFunction("AddCollider", &LuaManager::AddCollider)
        .addFunction("SetVelocity", &LuaManager::SetVelocity)
        .addFunction("SetTexture", &LuaManager::SetTexture)
        .addFunction("AddGameObject", &LuaManager::AddGameObject)
        .addFunction("CreateGameObject", &LuaManager::CreateGameObject)
        .endClass();

    luabridge::push(L, this);
    lua_setglobal(L, "LuaManager");

    if (luaL_dofile(L, "Scripts\\config.lua")) {
        std::cout << "Lua program returned an error: \n";
        std::cout << lua_tostring(L, -1);
        std::cout << std::endl;
        lua_close(L);
    }
}

void LuaManager::Update(double frameTime)  {

}
    
GameObject* LuaManager::CreateGameObject() {
    return new GameObject();
}

GameObject* LuaManager::SetPosition(GameObject *obj, float x, float y, float z) {
    obj->transform.translation.x = x;
    obj->transform.translation.y = y;
    obj->transform.translation.z = z;
    return obj;
}

GameObject* LuaManager::SetRotation(GameObject *obj, float x, float y, float z) {
    obj->transform.rotation.x = x;
    obj->transform.rotation.y = y;
    obj->transform.rotation.z = z;
    return obj;
}

GameObject* LuaManager::SetScale(GameObject *obj, float x, float y, float z) {
    obj->transform.scale.x = x;
    obj->transform.scale.y = y;
    obj->transform.scale.z = z;
    return obj;
}

GameObject* LuaManager::AddCollider(GameObject *obj) {
    obj->collider = new Collider(obj->transform.translation);
    return obj;
}

GameObject* LuaManager::SetVelocity(GameObject *obj, float x, float y, float z) {
    obj->collider->velocity.x = x;
    obj->collider->velocity.y = y;
    obj->collider->velocity.z = z;
    return obj;
}

GameObject* LuaManager::SetTexture(GameObject *obj, std::string textureName) {
    obj->texture = core->textures[textureName];
    return obj;
}

void LuaManager::AddGameObject(GameObject *obj) {
    core->AddGameObject(obj);
}