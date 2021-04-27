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
		draw(*gameObj);
	}
}

// was taken from here https://learnopengl.com/In-Practice/Text-Rendering
void Renderer::drawText(Text& text) const {
    // Activate corresponding render state
    text.getShader()->bind();
    text.getShader()->setUniform3f("textColor", text.Color.r, text.Color.g, text.Color.b);
    text.getShader()->setUniformMat4f("projection", m_Projection);
    glCall(glActiveTexture(GL_TEXTURE0));
    text.getVAO()->bind();
    text.getIBO()->bind();

    const float scale = 1.0f;
    float x = text.Position.x;
    float y = text.Position.y;
    // Iterate through all characters
    for (auto c = text.getText().begin(); c != text.getText().end(); ++c) {
        const ResourceManager::Character ch = ResourceManager::s_Characters[*c];

        const float xpos = x + ch.Bearing.x * scale;
        const float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        const float w = ch.Size.x * scale;
        const float h = ch.Size.y * scale;
        // Update VBO for each character
        float vertices[] = {
             xpos, ypos + h,     0.0f, 0.0f,
             xpos, ypos,         0.0f, 1.0f,
             xpos + w, ypos,     1.0f, 1.0f,
             xpos + w, ypos + h, 1.0f, 0.0f
        };
        // Render glyph texture over quad
        glCall(glBindTexture(GL_TEXTURE_2D, ch.TextureID));
        // Update content of VBO memory
        glCall(glBindBuffer(GL_ARRAY_BUFFER, text.getVBO()->getId()));
        glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices));
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
        glCall(glDrawElements(GL_TRIANGLES, text.getIBO()->getCount(), GL_UNSIGNED_INT, nullptr));
        // Render quad
        // Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
    }
    glCall(glBindVertexArray(0));
    glCall(glBindTexture(GL_TEXTURE_2D, 0));
}
