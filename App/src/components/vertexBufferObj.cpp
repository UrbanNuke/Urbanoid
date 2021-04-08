#include "vertexBufferObj.h"
#include <GL/glew.h>
#include "renderer.h"


VertexBufferObj::VertexBufferObj(const void* data, const unsigned int size) {
	glCall(glGenBuffers(1, &m_RendererId));								// generate new buffer with size = 1
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));				// bind our buffer to STATE MACHINE GL_ARRAY_BUFFER = for vertex attributes

	
	glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));	// GL_ARRAY_BUFFER - which the buffer object is bound, size - size of values, data - pointer to our dataArr,
																	    // GL_STATIC_DRAW - how we should use that data (how a buffer object's data store will be accessed).
}

VertexBufferObj::~VertexBufferObj() {
	glCall(glDeleteBuffers(1, &m_RendererId));
}

void VertexBufferObj::Bind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererId));
}


void VertexBufferObj::Unbind() const {
	glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
