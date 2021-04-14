#pragma once
#include <array>
#include "indexBufferObj.h"
#include "shader.h"
#include "vertexArrayObj.h"
#include "../components/gameObjects/gameObject.h"


#define ASSERT(x) if (!(x)) __debugbreak();
#define glCall(x) glClearError();\
	x;\
	ASSERT(glLogCall(#x, __FILE__, __LINE__));\

void glClearError();
bool glLogCall(const char* fn, const char* file, const int line);

class Renderer {

public:
	void clear() const;
	void draw(const VertexArrayObj& vao, const IndexBufferObj& ibo, const Shader& shader) const;
	void draw(GameObject& gameObj) const;
};