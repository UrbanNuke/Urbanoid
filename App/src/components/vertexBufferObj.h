#pragma once

class VertexBufferObj {
	unsigned int m_RendererId;

public:
	VertexBufferObj(const void* data, const unsigned int size);
	~VertexBufferObj();

	void bind() const;
	void unbind() const;
};
