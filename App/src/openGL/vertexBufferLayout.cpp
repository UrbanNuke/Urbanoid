#include "vertexBufferLayout.h"
#include <GL/glew.h>
#include "renderer.h"

unsigned int VertexBufferObjElement::getSizeOfType(const unsigned int type) {
	switch (type) {
	case GL_FLOAT:
	case GL_UNSIGNED_INT:
		return 4;
	case GL_UNSIGNED_BYTE:
		return 1;
	default:
		ASSERT(false)
			return 0;
	}
}

template <typename T>
void VertexBufferLayout::push(unsigned int count) {
	static_assert(false);
}

template <>
void VertexBufferLayout::push<float>(const unsigned int count) {
	m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
	m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_FLOAT);
}

template <>
void VertexBufferLayout::push<unsigned int>(const unsigned int count) {
	m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
	m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_UNSIGNED_INT);
}

template <>
void VertexBufferLayout::push<unsigned char>(const unsigned int count) {
	m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
	m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_UNSIGNED_BYTE);
}