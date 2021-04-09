#pragma once
#include "vertexBufferLayout.h"
#include "vertexBufferObj.h"

class VertexArrayObj {
	unsigned int m_RendererId;
public:
	VertexArrayObj();
	~VertexArrayObj();

	void addVertexBufferObj(const VertexBufferObj& vbo, const VertexBufferLayout& layout);

	void bind() const;
	void unbind() const;
};

