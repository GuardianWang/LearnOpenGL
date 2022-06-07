#include "Texture.h"

Texture::Texture() : m_target(GL_TEXTURE_2D) {
	glGenTextures(1, &m_id);
}

Texture::Texture(const char* path, GLenum target, GLenum texture, 
	GLuint level, GLuint internalformat, GLint border, GLenum format, GLenum type) : m_target(target) {
	// read image
	int w, h, c;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(path, &w, &h, &c, 0);
	
	// texture
	glGenTextures(1, &m_id);
	glActiveTexture(texture);
	bind();

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(target, level, internalformat, w, h, border, format, type, bytes);
	glGenerateMipmap(target);  // necessary

	stbi_image_free(bytes);
	unbind();
}

Texture::~Texture() {
	glDeleteTextures(1, &m_id);
}

void Texture::bind() {
	glBindTexture(m_target, m_id);
}

void Texture::unbind() {
	glBindTexture(m_target, 0);
}

void Texture::uniform(const GLchar* name, GLint v0) {
	GLuint u_tex = glGetUniformLocation(m_id, name);
	glUniform1i(u_tex, v0);
}
