#version 330

uniform mat4 modelMatrix;
uniform mat4 viewMatrix, viewMatrixInverse;
uniform mat4 projectionMatrix;

uniform vec3 lightPosition;

in vec4 vertex;
in vec3 vertexNormal;
in vec2 vertexTexture;

out vec3 normal, view, lightDir;
out vec2 texCoord;

void main()
{
	texCoord = vertexTexture;
	normal = vertexNormal;
	vec3 worldCoordinate = vec3(modelMatrix * vertex);
    view = (viewMatrixInverse*vec4(0,0,0,1)).xyz - worldCoordinate;
	lightDir = lightPosition - worldCoordinate;
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vertex;
}