#include "Precompiled.h"
#include "GraphicsManager.h"
#include "GameObject.h"
#include "Core.h"

void LoadObj(std::string file) { 

}

GraphicsManager::GraphicsManager(Core *core) : IManager(core) { 
    // Glew / DevIL
    glewExperimental = GL_TRUE;
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

void GraphicsManager::Update(double frameTime) { 
    int windowWidth, windowHeight;
    glfwGetWindowSize(core->window, &windowWidth, &windowHeight);


    GLfloat color[4]= {0.2f, 0.4f, 0.8f, 1.0f};

    glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
    glFogfv(GL_FOG_COLOR, color);            // Set Fog Color
    //glFogf(GL_FOG_DENSITY, 0.15f);              // How Dense Will The Fog Be
    glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
    glFogf(GL_FOG_START, 25);             // Fog Start Depth
    glFogf(GL_FOG_END, 50);               // Fog End Depth
    glEnable(GL_FOG);                   // Enables GL_FOG

    // Clear the screen to background color
    glClearColor(color[0], color[1], color[2], color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, windowWidth / windowHeight, 0.1, 50); 

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -core->gameObjects[0]->transform.translation.z - 5);

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
    }

    // Swap buffers
    glfwSwapBuffers(core->window);
    glfwPollEvents();
}