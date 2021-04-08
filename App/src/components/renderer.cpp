#include "renderer.h"
#include <GL/glew.h>
#include <iostream>

void glClearError() {
	while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* fn, const char* file, const int line) {
	while (const GLenum error = glGetError()) {
		std::cout << "[OpenGL Error] (" << error << "): " << fn << " " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}
