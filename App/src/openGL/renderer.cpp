#include "renderer.h"
#include <GL/glew.h>
#include <iostream>
#include "glm/gtc/matrix_transform.hpp"

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

Renderer::Renderer(const unsigned int screenWidth, const unsigned int screenHeight)
	: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
{
	m_Projection = glm::ortho(
		0.0f, static_cast<float>(screenWidth), 0.0f, static_cast<float>(screenHeight), -1.0f, 1.0f
	);

	glCall(glEnable(GL_BLEND));
	glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
}

Renderer::~Renderer() {
	
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

void Renderer::draw(const GameObject& gameObj) const {
	gameObj.getShader()->bind();
	const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj.Position.x, gameObj.Position.y, 0.0f));
	const glm::mat4 mvp = m_Projection * model;
	gameObj.getShader()->setUniformMat4f("u_MVP", mvp);
	gameObj.getShader()->setUniform4f("u_Color", gameObj.Color.r, gameObj.Color.g, gameObj.Color.b, gameObj.Color.a);
	gameObj.getTexture2D()->bind();
	gameObj.getVAO()->bind();
	gameObj.getIBO()->bind();
	glCall(glDrawElements(GL_TRIANGLES, gameObj.getIBO()->getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::draw(const std::vector<GameObject*> list) const {

	for (auto gameObj : list) {
		gameObj->getShader()->bind();
		const glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(gameObj->Position.x, gameObj->Position.y, 0.0f));
		const glm::mat4 mvp = m_Projection * model;
		gameObj->getShader()->setUniformMat4f("u_MVP", mvp);
		gameObj->getShader()->setUniform4f("u_Color", gameObj->Color.r, gameObj->Color.g, gameObj->Color.b, gameObj->Color.a);
		gameObj->getTexture2D()->bind();
		gameObj->getVAO()->bind();
		gameObj->getIBO()->bind();
		glCall(glDrawElements(GL_TRIANGLES, gameObj->getIBO()->getCount(), GL_UNSIGNED_INT, nullptr));
	}
	
}
