#pragma once
#include <vector>
#include <GL/glew.h>

struct VertexBufferObjElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(const unsigned int type);
};

class VertexBufferLayout {
	std::vector<VertexBufferObjElement> m_Elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout(): m_Stride(0) {
	};

	template <typename T>
	void push(unsigned int count) {
		static_assert(false);
	}

	template <>
	void push<float>(const unsigned int count) {
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_FLOAT);
	}

	template <>
	void push<unsigned int>(const unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_UNSIGNED_INT);
	}

	template <>
	void push<unsigned char>(const unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferObjElement::getSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline const std::vector<VertexBufferObjElement>& getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};
