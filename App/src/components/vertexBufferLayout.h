#pragma once
#include <vector>

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
	void push(unsigned int count);

	template <>
	void push<float>(const unsigned int count);

	template <>
	void push<unsigned int>(const unsigned int count);

	template <>
	void push<unsigned char>(const unsigned int count);

	inline const std::vector<VertexBufferObjElement>& getElements() const { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }
};
