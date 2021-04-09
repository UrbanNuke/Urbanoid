#include "vertexArrayObj.h"
#include <GL/glew.h>
#include "renderer.h"

VertexArrayObj::VertexArrayObj() {
	glCall(glGenVertexArrays(1, &m_RendererId));
}

VertexArrayObj::~VertexArrayObj() {
	glCall(glDeleteVertexArrays(1, &m_RendererId));
}

void VertexArrayObj::addVertexBufferObj(const VertexBufferObj& vbo, const VertexBufferLayout& layout) {
	bind();
	vbo.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); ++i) {
		const auto& element = elements[i];
		glCall(glEnableVertexAttribArray(i)); // enable vertex attributes Array

		/**
		 *  i - which layout in shader is used, count - count of one element(vertex), type - what kind of data we use,
		 *  normalized - normalization, stride - how many bites takes one vert, offset
		 */
		glCall(glVertexAttribPointer(
			i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset)
		);
		offset += element.count * VertexBufferObjElement::getSizeOfType(element.type);
	}
}

void VertexArrayObj::bind() const {
	glCall(glBindVertexArray(m_RendererId));
}

void VertexArrayObj::unbind() const {
	glCall(glBindVertexArray(0));
}
