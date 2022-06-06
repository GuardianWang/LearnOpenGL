#pragma once
#include <glad/gl.h>

class VAO {
public:
	VAO();
	~VAO();

	void bind();
	void unbind();
	void link(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
	void unlink(GLuint index);

public:
	GLuint m_id;
};

