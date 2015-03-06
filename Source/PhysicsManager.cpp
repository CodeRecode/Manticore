#include "PhysicsManager.h"
#include "GameObject.h"
#include "Core.h"

PhysicsManager::PhysicsManager(Core* core) : IManager(core) {

}

void PhysicsManager::Update(double frameTime) { 
    GameObject *obj;
    for (int i = 0; i < core->MAX_GAME_OBJECTS; i++) {
        obj = core->gameObjects[i];
        if (obj && obj->collider) {
            obj->collider->position += obj->collider->velocity * float(frameTime);
        }
    }
}