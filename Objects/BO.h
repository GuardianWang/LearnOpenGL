#pragma once
#include <glad/gl.h>

class BO {
public:
	BO();
	BO(GLenum target);
	BO(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	~BO();

	void bind(GLsizeiptr size, const void* data, GLenum usage);
	void bind(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
	void unbind();

public:
	GLuint m_id;
	GLenum m_target;
};

