#pragma once
#include "Precompiled.h"
#include "IManager.h"
#include "Texture.h"
#include "GameObject.h"

enum class GameState {
    None,
    Running,
    Paused
};

class Core 
{
public:
    GLFWwindow *window;
    static const int INIT_WINDOW_WIDTH = 640,
        INIT_WINDOW_HEIGHT = 480,
        MAX_GAME_OBJECTS = 2048;

    bool quit;
    double lastXPos, lastYPos;
    std::map<std::string, Texture*> textures;
    GameObject *gameObjects[MAX_GAME_OBJECTS];

	glm::vec3 cameraTranslation, cameraRotation;

    Core();
    ~Core();

    void LoadTextures();

    void StartGame();
    void UpdateGame();
    void EndGame();

    void AddGameObject(GameObject *obj);

private:
	std::vector<IManager *> managers;
	const std::string windowTitle;
};