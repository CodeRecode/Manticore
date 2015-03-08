#include "Precompiled.h"
#include "Core.h"
#include "GraphicsManager.h"
#include "PhysicsManager.h"
#include "LuaManager.h"

void Core::LoadTextures() {
    std::ifstream textureFile("Textures\\texturelist.txt");
    std::string name, path, line;
    while (std::getline(textureFile, line))
    {
        std::istringstream iss(line);
        iss >> name >> path;
        textures[name] = new Texture(path);
    }
}

Core::Core() : windowTitle("Manticore Engine"), quit(false) 
{
    // Initialize window
    glfwInit();
    window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, windowTitle.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwGetCursorPos(window, &lastXPos, &lastYPos);

    // Initialize managers
    managers.push_back(new GraphicsManager(this));
    managers.push_back(new PhysicsManager(this));

    LoadTextures();
    std::fill(gameObjects, gameObjects + MAX_GAME_OBJECTS, nullptr);

    managers.push_back(new LuaManager(this));
}

Core::~Core() 
{

}

void Core::StartGame() 
{
	for (int i = 0; i < managers.size(); ++i)
	{
		managers[i]->Init();
	}
}

void Core::UpdateGame() 
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window)) {        
        quit = true;
    }

    if (glfwGetKey(window, GLFW_KEY_A) != 0) {
        gameObjects[0]->transform.translation.x -= .05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_D) != 0) {
        gameObjects[0]->transform.translation.x += .05f;
    }

    if (glfwGetKey(window, GLFW_KEY_W) != 0) {
        gameObjects[0]->transform.translation.y += .05f;
    }
    else if (glfwGetKey(window, GLFW_KEY_S) != 0) {
        gameObjects[0]->transform.translation.y -= .05f;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) != 0) {
        gameObjects[0]->transform.rotation.z += 6.f;
    }

    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    gameObjects[1]->transform.translation.x += float(xPos - lastXPos) * .01f;
    gameObjects[1]->transform.translation.y -= float(yPos - lastYPos) * .01f;

    lastXPos = xPos;
    lastYPos = yPos;

    for (unsigned int i = 0; i < managers.size(); ++i) {
        managers[i]->Update(1.0 / 60.0);
    }
}

void Core::EndGame() 
{
	for (int i = 0; i < managers.size(); ++i)
	{
		managers[i]->CleanUp();
	}
}

void Core::AddGameObject(GameObject *obj) 
{    
    for (int i = 0; i < MAX_GAME_OBJECTS; i++) 
	{
        if(gameObjects[i] == nullptr) 
		{
            gameObjects[i] = obj;
            break;
        }
    }
}