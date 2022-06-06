#pragma once
#include <glad/gl.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

class Shader
{
public:
	Shader(const char* vertexFile, const char* fragmentFile);
	~Shader();

	void use();

public:
	GLuint m_id;

private:
	void compileErrors(unsigned int shader, const char* type);
};

