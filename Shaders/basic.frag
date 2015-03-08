#version 330

uniform sampler2D modelTexture;

in vec3 normal;
in vec2 texCoord;

out vec4 outColor;

void main()
{
	vec4 diffuse = texture(modelTexture, texCoord);
	outColor = diffuse;
}