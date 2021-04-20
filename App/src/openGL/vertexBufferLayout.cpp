#include "vertexBufferLayout.h"

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
