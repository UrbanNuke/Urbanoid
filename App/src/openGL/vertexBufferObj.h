#pragma once
#include <GL/glew.h>

class VertexBufferObj {
	unsigned int m_RendererId;

public:
	VertexBufferObj(const void* data, const unsigned int size, const int drawType = GL_STATIC_DRAW);
	~VertexBufferObj();

	void bind() const;
	void unbind() const;

	inline unsigned int getId() const { return m_RendererId; }
};
