#pragma once

#include <unordered_map>
#include <string>
#include "../openGL/shader.h"


class ResourceManager {

public:
	static std::unordered_map<std::string, Shader> s_Shaders;

private:
	ResourceManager() {};
public:
	static Shader& loadShader(const unsigned int shader, const std::string& name);
	static Shader& getShader(const std::string& name);
	static void clear();
};

