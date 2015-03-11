#version 330

uniform sampler2D modelTexture;

in vec3 normal, view, lightDir;
in vec2 texCoord;

out vec4 outColor;

void main()
{
	vec3 N = normalize(normal);
	vec3 V = normalize(view);
	vec3 L = normalize(lightDir);
	vec3 H = normalize(V + L);
	float HdotL = dot(H, L);
	float NdotL = dot(N, L);
	float PI = 3.141592;
	
	float alpha = 10;
	vec3 diffuse = texture(modelTexture, texCoord).xyz;
	vec3 specular = vec3(.04, .04, .04);
	
	vec3 F = specular + (1 - specular) * pow((1 - dot(L, H)), 5);
	float D = ((alpha + 2) / (2 * PI)) * pow(max(0.0, dot(H, N)), alpha);
	float G = 1 / (HdotL * HdotL);
	
	vec3 ambient = diffuse * .25;
	vec3 brdf = max(0.0, NdotL) * (diffuse + F * D * G);
	
	outColor = vec4(ambient + brdf, 1);
}