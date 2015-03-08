#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

in vec3 vertex;
in vec3 vertexNormal;
in vec2 vertexTexture;

out vec3 normal;
out vec2 texCoord;

void main()
{
	texCoord = vertexTexture;
	normal = vertexNormal;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertex, 1);
}