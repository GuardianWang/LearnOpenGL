#include "BO.h"

BO::BO() : m_target(GL_ARRAY_BUFFER) {
	glGenBuffers(1, &m_id);
}

BO::BO(GLenum target) : m_target(target) {
	glGenBuffers(1, &m_id);
}

BO::BO(GLenum target, GLsizeiptr size, const void* data, GLenum usage) : m_target(target) {
	glGenBuffers(1, &m_id);
	bind(size, data, usage);
}

BO::~BO() {
	glDeleteBuffers(1, &m_id);
}

void BO::bind(GLsizeiptr size, const void* data, GLenum usage) {
	glBindBuffer(m_target, m_id);
	glBufferData(m_target, size, data, usage);
}

void BO::bind(GLenum target, GLsizeiptr size, const void* data, GLenum usage) {
	m_target = target;
	bind(size, data, usage);
}

void BO::unbind() {
	glBindBuffer(m_target, 0);
}
