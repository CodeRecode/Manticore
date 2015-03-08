#include "Shader.h"

void ShaderProgram::Initialize()
{
	Create();
	Load(".vert", GL_VERTEX_SHADER);
	Load(".frag", GL_FRAGMENT_SHADER);
	Link();
}

void ShaderProgram::Bind()
{
	glUseProgram(program);
}

void ShaderProgram::UnBind()
{
	glUseProgram(0);
}

void ShaderProgram::Create()
{
	program = glCreateProgram();
}

void ShaderProgram::Load(std::string fileType, GLenum type)
{
	std::ifstream shaderFile("./Shaders/" + fileName + fileType);
	std::string shaderSource((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	const GLchar *pSource = shaderSource.c_str();

	GLint shader = glCreateShader(type);
	glAttachShader(program, shader);
	glShaderSource(shader, 1, &pSource, NULL);
	glCompileShader(shader);

	int status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != 1)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* buffer = new char[length];
		glGetShaderInfoLog(shader, length, NULL, buffer);
		printf("Compile log for %s:\n%s\n", fileName.c_str(), buffer);
		delete buffer;
	}
}

void ShaderProgram::Link()
{
	glLinkProgram(program);

	int status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);

	// If link failed, get and print log
	if (status != 1) {
		int length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		char* buffer = new char[length];
		glGetProgramInfoLog(program, length, NULL, buffer);
		printf("Link log:\n%s\n", buffer);
		delete buffer;
	}
}