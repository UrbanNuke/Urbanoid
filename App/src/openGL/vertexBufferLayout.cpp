#include "vertexBufferLayout.h"

#include <iostream>

unsigned int VertexBufferObjElement::getSizeOfType(const unsigned int type) {
	switch (type) {
		case GL_FLOAT:
		case GL_UNSIGNED_INT:
			return 4;
		case GL_UNSIGNED_BYTE:
			return 1;
		default:
			std::cout << "ERROR: wrong size of type" << std::endl;
				return 0;
	}
}
