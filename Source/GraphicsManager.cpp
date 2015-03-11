#include "Precompiled.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Core.h"
#include "Mesh.h"

GraphicsManager::GraphicsManager(Core *core) : IManager(core), basicShader("basic")
{
	glewInit();
	ilInit();

	// OpenGL Settings
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glAlphaFunc(GL_GREATER, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicsManager::Init()
{
	basicShader.Initialize();
	m = new Model(new Texture("./Models/cube.tga"), new Mesh());
}

void GraphicsManager::Update(double frameTime)
{
	int windowWidth, windowHeight;
	glfwGetWindowSize(core->window, &windowWidth, &windowHeight);

	// Clear the screen to background color
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, windowWidth, windowHeight);

	float sx, sy;
	sy = 0.6f* .1f;
	sx = sy * windowWidth / windowHeight;

	glm::mat4x4 T1 = glm::rotate(glm::mat4(1.0), core->cameraRotation.y, glm::vec3(1, 0, 0));
	glm::mat4x4 T2 = glm::rotate(T1, core->cameraRotation.x, glm::vec3(0, 1, 0));
	glm::mat4x4 WorldView = glm::translate(T2, core->cameraTranslation);
	glm::mat4x4 WorldProj = glm::frustum(-sx, sx, -sy, sy, .1f, 10000.0f);

	basicShader.Bind();
	int program = basicShader.GetShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, value_ptr(WorldProj));
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, value_ptr(WorldView));
	glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrixInverse"), 1, GL_FALSE, value_ptr(glm::inverse(WorldView)));
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, value_ptr(glm::mat4(1.f)));

	float lightPosition[3] = { 1, 1, 1 };
	glUniform3fv(glGetUniformLocation(program, "lightPosition"), 1, lightPosition);

	m->Draw(&basicShader);
	basicShader.UnBind();

	PrintGLError();
}

void GraphicsManager::PrintGLError()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << " - " << gluErrorString(err) << std::endl;
	}
}