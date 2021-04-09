#pragma once

class IndexBufferObj {
	unsigned int m_RendererId;
	unsigned int m_Count;

public:
	IndexBufferObj(const void* data, const unsigned int count);
	~IndexBufferObj();

	void bind() const;
	void unbind() const;
};
