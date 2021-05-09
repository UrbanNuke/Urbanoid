#pragma once
#include "vertexBufferLayout.h"
#include "vertexBufferObj.h"

class VertexBufferLayout;

class VertexArrayObj {
	unsigned int m_RendererId;
public:
	VertexArrayObj();
	~VertexArrayObj();

	void addVertexBufferObj(const VertexBufferObj& vbo, const VertexBufferLayout& layout) const;

	void bind() const;
	void unbind() const;
};

