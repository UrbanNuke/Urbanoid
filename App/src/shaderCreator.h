#pragma once
#include <string>

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static unsigned int compileShader(const unsigned int type, const std::string& source);

unsigned int createShader(unsigned int shader);

static ShaderProgramSource parseShader(const std::string_view& filepath);