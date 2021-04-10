#include "resourceManager.h"
#include "../openGL/renderer.h"

std::unordered_map<std::string, Shader> ResourceManager::s_Shaders;

Shader& ResourceManager::loadShader(const unsigned int shader, const std::string& name) {
	Shader newShader(shader);
	s_Shaders.insert_or_assign(name,newShader);
	return s_Shaders.at(name);
}

Shader& ResourceManager::getShader(const std::string& name) {
	if (s_Shaders.find(name) == s_Shaders.end()) {
		ASSERT(false);
	}
	return s_Shaders.at(name);
}

void ResourceManager::clear() {
	// (properly) delete all shaders
	for (auto [name, shader] : s_Shaders) {
		shader.deleteShader();
	}
}
