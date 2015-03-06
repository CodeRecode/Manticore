#include "Texture.h"

Texture::Texture(std::string fileName) : scale(1) {
    int textureWidth, textureHeight;

    GLuint id;
    glGenTextures(1, &id);

    // Load and convert the image with DevIL
    ILuint imageID;	
    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    ilLoadImage(fileName.c_str());
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    iluFlipImage();

    textureWidth = ilGetInteger(IL_IMAGE_WIDTH);
    textureHeight = ilGetInteger(IL_IMAGE_HEIGHT);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), textureWidth, textureHeight,
        0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());
    ilDeleteImage(imageID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR 	);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, NULL);

    textureId = id;
}

Texture::~Texture() {
    glDeleteTextures(1, &(GLuint)textureId);
}

void Texture::Draw() {
    glBindTexture(GL_TEXTURE_2D, (GLuint)textureId);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0); 
    glVertex2f(-.5, -.5);

    glTexCoord2f(0, scale); 
    glVertex2f(-.5, .5);

    glTexCoord2f(scale, scale); 
    glVertex2f(.5, .5);

    glTexCoord2f(scale, 0); 
    glVertex2f(.5, -.5);

    glEnd();

    glBindTexture(GL_TEXTURE_2D, NULL);
}