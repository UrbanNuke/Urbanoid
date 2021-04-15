#include "resourceManager.h"
#include "../openGL/renderer.h"

std::unordered_map<std::string, Shader*> ResourceManager::s_Shaders;
std::unordered_map<std::string, Texture2D*> ResourceManager::s_Textures2D;

Shader* ResourceManager::loadShader(const unsigned int shader, const std::string& name) {
	Shader* newShader = new Shader(shader);
	s_Shaders[name] = newShader;
	return s_Shaders[name];
}

Shader* ResourceManager::getShader(const std::string& name) {
	if (s_Shaders.find(name) == s_Shaders.end()) {
		ASSERT(false);
	}
	return s_Shaders[name];
}

Texture2D* ResourceManager::loadTexture2D(const unsigned texture, const std::string& name) {
	Texture2D* newTexture2D = new Texture2D(texture);
	s_Textures2D[name] = newTexture2D;
	return s_Textures2D[name];
}

Texture2D* ResourceManager::getTexture2D(const std::string& name) {
	if (s_Textures2D.find(name) == s_Textures2D.end()) {
		ASSERT(false);
	}
	return s_Textures2D[name];
}

void ResourceManager::clear() {
	// (properly) delete all shaders
	for (auto [name, shader] : s_Shaders) {
		delete shader;
	}

	for (auto [name, texture] : s_Textures2D) {
		delete texture;
	}

	s_Shaders.clear();
	s_Textures2D.clear();
}
