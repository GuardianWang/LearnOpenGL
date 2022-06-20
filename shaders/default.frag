#version 330 core

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 worldCoord;

out vec4 FragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main() {
	float ambient = .2f;

	vec3 vert2light = normalize(lightPos - worldCoord);
	float diffuse = max(0.f, dot(normal, vert2light));

	float specular = .5f;
	vec3 reflectDir = reflect(-vert2light, normal);
	vec3 vert2eye = normalize(camPos - worldCoord);
	float specAmount = pow(max(dot(vert2eye, reflectDir), 0.0f), 8);
	specular = specular * specAmount * texture(tex1, texCoord).r;

	FragColor = texture(tex0, texCoord) * lightColor * (diffuse + ambient) + 
				specular * lightColor;
}
