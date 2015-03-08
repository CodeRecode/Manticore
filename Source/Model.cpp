#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

void Model::Draw(ShaderProgram * shader)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->GetTextureId());
	glUniform1i(glGetUniformLocation(shader->program, "modelTexture"), 0);

	mesh->Draw();

	glBindTexture(GL_TEXTURE_2D, 0);
}