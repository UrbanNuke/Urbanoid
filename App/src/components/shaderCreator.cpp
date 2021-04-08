#include "shaderCreator.h"

#include <iostream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include "../resource.h"

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

unsigned int createShader(unsigned int shader) {
	const unsigned int program = glCreateProgram();
	const Resource res(shader, "SHADER");
	const ShaderProgramSource source = parseShader(res.GetResourceString());
	const unsigned int vs = compileShader(GL_VERTEX_SHADER, source.VertexSource);
	const unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.FragmentSource);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	
	int program_linked;
	glGetProgramiv(program, GL_LINK_STATUS, &program_linked);
	if (program_linked != GL_TRUE) {
		int log_length = 0;
		char message[1024];
		glGetProgramInfoLog(program, 1024, &log_length, message);
		std::cout << "Failed to link program" << std::endl;
		std::cout << message << std::endl;
	}
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;
}

static ShaderProgramSource parseShader(const std::string_view& shader) {
	std::stringstream stream[3];
	stream[0] << shader;
	
	enum class ShaderType {
		None = 0, Vertex = 1, Fragment = 2
	};
	
	std::string line;
	ShaderType shaderType = ShaderType::None;
	while (getline(stream[0], line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				shaderType = ShaderType::Vertex;
			} else if (line.find("fragment") != std::string::npos) {
				shaderType = ShaderType::Fragment;
			}
		} else {
			stream[(int)shaderType] << line << '\n'; // TODO: find out that thing
		}
	}

	return { stream[1].str() , stream[2].str() };
}
