#include "shader.h"
#include <iostream>
#include <sstream>
#include <GL/glew.h>

#include "renderer.h"
#include "../resource.h"

Shader::Shader(const unsigned shader) : m_RendererId(0) {
	m_RendererId = createShader(shader);
}

Shader::~Shader() {
	glCall(glDeleteProgram(m_RendererId));
}

void Shader::bind() const {
	glCall(glUseProgram(m_RendererId));
}

void Shader::unbind() const {
	glCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& name, const float v0, const float v1, const float v2, const float v3) {
	glCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

unsigned Shader::getUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	glCall(const int location = glGetUniformLocation(m_RendererId, name.c_str()));
	if (location == -1) {
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
	m_UniformLocationCache[name] = location;
	return location;
}

unsigned int Shader::compileShader(const unsigned int type, const std::string& source) {
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

unsigned int Shader::createShader(const unsigned int shader) {
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

ShaderProgramSource Shader::parseShader(const std::string_view& shader) const {
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