#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;
layout (location = 3) in vec3 aNormal;

out vec3 color;
out vec2 texCoord;
out vec3 normal;
out vec3 worldCoord;

uniform float scale;
uniform mat4 model;
uniform mat4 camera;

void main() {
	
	vec4 worldCoord4 = model * vec4(aPos * scale, 1.0);
	worldCoord = worldCoord4.xyz;
	gl_Position = camera * worldCoord4;
	color = aColor;
	texCoord = aTex;
	normal = normalize(vec3(model * vec4(aNormal, 0.f)));
}
