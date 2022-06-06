#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &m_id);
	bind();
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &m_id);
}

void VAO::bind() {
	glBindVertexArray(m_id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::link(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	glEnableVertexAttribArray(index);
}

void VAO::unlink(GLuint index) {
	glDisableVertexAttribArray(index);
}
