#pragma once
#include <string>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static unsigned int compileShader(const unsigned int type, const std::string& source);

unsigned int createShader(const std::string& filepath);

static ShaderProgramSource parseShader(const std::string& filepath);