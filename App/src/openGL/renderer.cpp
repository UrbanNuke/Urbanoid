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

void Renderer::clear() const {
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::draw(const VertexArrayObj& vao, const IndexBufferObj& ibo, const Shader& shader) const {
	shader.bind();
	vao.bind();
	ibo.bind();
	glCall(glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(GameObject& gameObj) const {
	gameObj.getShader()->bind();
	gameObj.getVAO()->bind();
	gameObj.getIBO()->bind();
	glCall(glDrawElements(GL_TRIANGLES, gameObj.getIBO()->getCount(), GL_UNSIGNED_INT, nullptr));
}
