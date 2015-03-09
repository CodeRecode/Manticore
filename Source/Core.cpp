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

Core::Core() : windowTitle("Manticore Engine"), quit(false), cameraTranslation(0, -1, -1), cameraRotation(0)
{
	// Initialize window
	glfwInit();
	window = glfwCreateWindow(INIT_WINDOW_WIDTH, INIT_WINDOW_HEIGHT, windowTitle.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &lastXPos, &lastYPos);

	// Add managers
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

	float pi = glm::pi<float>(), speed = .1;

	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	cameraRotation.x += float(xPos - lastXPos) * .01f;
	cameraRotation.y += float(yPos - lastYPos) * .01f;

	cameraRotation.y = glm::clamp(cameraRotation.y, -pi / 2.0f, pi / 2.0f);
	if (cameraRotation.x > pi)
		cameraRotation.x -= 2 * pi;
	else if (cameraRotation.x <= -pi)
		cameraRotation.x += 2 * pi;

	lastXPos = xPos;
	lastYPos = yPos;

	if (glfwGetKey(window, GLFW_KEY_A) != 0) {
		cameraTranslation.x += -cosf(cameraRotation.x + pi) * speed;
		cameraTranslation.z += -sinf(cameraRotation.x + pi) * speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_D) != 0) {
		cameraTranslation.x += cosf(cameraRotation.x - pi) * speed;
		cameraTranslation.z += sinf(cameraRotation.x - pi) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_W) != 0) {
		cameraTranslation.x += -sinf(cameraRotation.x) * speed;
		cameraTranslation.z += cosf(cameraRotation.x) * speed;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) != 0) {
		cameraTranslation.x += sinf(cameraRotation.x) * speed;
		cameraTranslation.z += -cosf(cameraRotation.x) * speed;
	}

	for (unsigned int i = 0; i < managers.size(); ++i) {
		managers[i]->Update(1.0 / 60.0);
	}

	// Swap buffers
	glfwSwapBuffers(window);
	glfwPollEvents();
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
		if (gameObjects[i] == nullptr)
		{
			gameObjects[i] = obj;
			break;
		}
	}
}