#include "shaderCreator.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int compileShader(const unsigned int type, const std::string& source) {
	const unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length * sizeof(char))); // TODO: why don't use _malloca? <- find out that thing
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: \n";
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}
	
	return id;
}

unsigned int createShader(const std::string& filepath) {
	const unsigned int program = glCreateProgram();
	const ShaderProgramSource source = parseShader(filepath);
	const unsigned int vs = compileShader(GL_VERTEX_SHADER, source.VertexSource);
	const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.FragmentSource);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	
	int program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE) {
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		// Write the error to a log
		std::cout << message << std::endl;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

static ShaderProgramSource parseShader(const std::string& filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType {
		None = -1, Vertex = 0, Fragment = 1
	};
	
	std::string line;
	std::stringstream ss[2];
	ShaderType shaderType = ShaderType::None;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				shaderType = ShaderType::Vertex;
			} else if (line.find("fragment") != std::string::npos) {
				shaderType = ShaderType::Fragment;
			}
		} else {
			ss[(int)shaderType] << line << '\n'; // TODO: find out that thing
		}
	}

	return { ss[0].str() , ss[1].str() };
}

