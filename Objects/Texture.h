#pragma once
#include <glad/gl.h>
#include <stb_image.h>

class Texture
{
public:
	Texture();
	Texture(const char* path, GLenum target, GLenum texture,
		GLuint level, GLuint internalformat, GLint border, GLenum format, GLenum type);
	~Texture();
	void bind();
	void unbind();
	void uniform(GLint shaderId, const GLchar* name, GLint v0);

public:
	GLuint m_id;
	GLenum m_target;
	GLenum m_texture;
};

