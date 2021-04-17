#pragma once

#include <unordered_map>
#include <string>
#include "../openGL/shader.h"
#include "../openGL/Texture2D.h"


class ResourceManager {

public:
	static std::unordered_map<std::string, Shader*> s_Shaders;
	static std::unordered_map<std::string, Texture2D*> s_Textures2D;

	static glm::vec4 s_RedColor;
	static glm::vec4 s_GreenColor;
	static glm::vec4 s_LightBlueColor;
	static glm::vec4 s_YellowColor;
	static glm::vec4 s_PinkColor;

private:
	ResourceManager() {};
public:
	static Shader* loadShader(const unsigned int shader, const std::string& name);
	static Shader* getShader(const std::string& name);
	static Texture2D* loadTexture2D(const unsigned int texture, const std::string& name);
	static Texture2D* getTexture2D(const std::string& name);
	static void clear();
};

