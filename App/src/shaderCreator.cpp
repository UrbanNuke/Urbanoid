#include "shaderCreator.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compileShader(unsigned int type, const std::string& source) {
	const unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: \n";
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	
	return id;
}

unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
	const unsigned int program = glCreateProgram();
	const unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

