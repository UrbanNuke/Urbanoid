#pragma once
#include "../components/gameObjects/gameObject.h"
#include "../components/gameObjects/text.h"
#include "glm/glm.hpp"

class VertexArrayObj;
class GameObject;

#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__));\

void glClearError();
bool glLogCall(const char* fn, const char* file, const int line);

class Renderer {
	unsigned int m_ScreenWidth, m_ScreenHeight;
	glm::mat4 m_Projection;

public:
	Renderer(const unsigned int screenWidth, const unsigned int screenHeight);
	~Renderer();
	void clear() const;
	void draw(const GameObject& gameObj) const;
	void draw(const std::vector<GameObject*>& list) const;
	void drawText(const Text& text) const;
	void drawText(const std::vector<Text*>& list) const;
};