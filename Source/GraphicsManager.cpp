#include "Precompiled.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Core.h"
#include "Mesh.h"

void LoadObj(std::string file) { 

}

GraphicsManager::GraphicsManager(Core *core) : IManager(core), sp("basic") { 
    // Glew / DevIL
    //glewExperimental = GL_TRUE;
    glewInit();
    ilInit();

    // OpenGL Settings
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glAlphaFunc(GL_GREATER, 0.5);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sp.Initialize();
	m = new Model(new Texture("./Models/cube.tga"), new Mesh());
}

void GraphicsManager::Update(double frameTime) { 
    int windowWidth, windowHeight;
    glfwGetWindowSize(core->window, &windowWidth, &windowHeight);
	
    // Clear the screen to background color
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, windowWidth, windowHeight);

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, windowWidth / windowHeight, 0.1, 50); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, core->gameObjects[0]->transform.translation.z - 5);

    GameObject *obj;
    for (int i = 0; i < core->MAX_GAME_OBJECTS; i++) {
        obj = core->gameObjects[i];
        if (obj && obj->texture) {
            Transform &trans = obj->transform;

            glPushMatrix();  

            glTranslatef(trans.translation.x, trans.translation.y, trans.translation.z);
            glRotatef(trans.rotation.x, 1, 0, 0);
            glRotatef(trans.rotation.y, 0, 1, 0);
            glRotatef(trans.rotation.z, 0, 0, 1);
            glScalef(trans.scale.x, trans.scale.y, trans.scale.z);

            obj->texture->Draw();
            glPopMatrix();
        }
    }*/


	float sx, sy;
	sy = 0.6f* .1f;
	sx = sy * windowWidth / windowHeight;

	glm::mat4x4 T1 = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
	glm::mat4x4 T2 = glm::rotate(T1, -60.f, glm::vec3(1, 0, 0));
	glm::mat4x4 WorldView = glm::lookAt(glm::vec3(core->gameObjects[0]->transform.translation.x, core->gameObjects[0]->transform.translation.y + .1, 2), glm::vec3(0), glm::vec3(0, 0, 1));  //glm::rotate(T2, -150.f, glm::vec3(0, 0, 1));
	glm::mat4x4 WorldProj = glm::frustum(-sx, sx, -sy, sy, .1f, 10000.0f);

	sp.Bind();


	int loc = glGetUniformLocation(sp.program, "projectionMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(WorldProj));
	loc = glGetUniformLocation(sp.program, "viewMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(WorldView));
	loc = glGetUniformLocation(sp.program, "modelMatrix");
	glUniformMatrix4fv(loc, 1, GL_FALSE, value_ptr(glm::mat4(1.f)));

	m->Draw(&sp);
	sp.UnBind();

	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cerr << "OpenGL error: " << err << " - " << gluErrorString(err) << std::endl;
	}

    // Swap buffers
    glfwSwapBuffers(core->window);
    glfwPollEvents();
}