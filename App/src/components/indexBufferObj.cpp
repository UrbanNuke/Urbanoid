#include "indexBufferObj.h"
#include <GL/glew.h>
#include "renderer.h"


IndexBufferObj::IndexBufferObj(const void* data, const unsigned int count)
	: m_Count(count)
{
	glCall(glGenBuffers(1, &m_RendererId));								// generate new buffer with size = 1
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));		// bind our buffer to STATE MACHINE GL_ELEMENT_ARRAY_BUFFER = for Index attributes

	
	glCall(glBufferData(												// GL_ELEMENT_ARRAY_BUFFER - which the buffer object is bound, size - size of values, data - pointer to our dataArr,
		GL_ELEMENT_ARRAY_BUFFER, 										// GL_STATIC_DRAW - how we should use that data (how a buffer object's data store will be accessed).
		count * sizeof(unsigned int), 
		data, GL_STATIC_DRAW)
	);																	
}

IndexBufferObj::~IndexBufferObj() {
	glCall(glDeleteBuffers(1, &m_RendererId));
}

void IndexBufferObj::Bind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId));
}


void IndexBufferObj::Unbind() const {
	glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
