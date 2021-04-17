#include "brick.h"

#include <GL/glew.h>

#include "../../openGL/indexBufferObj.h"

Brick::Brick(const glm::vec2& position, const std::string& texture, const std::string& shader, const glm::vec2& size)
	: GameObject(position, texture, shader)
{
	m_Type = Shape::Brick;
	createMesh(size);
}

Brick::~Brick() {
}

void Brick::createMesh(const glm::vec2& size) {

	//first pair - vertex, second - texture
	m_Mesh.push_back(glm::vec2(-size.x, -size.y));
	m_Mesh.push_back(glm::vec2(0.0f, 0.0f));

	m_Mesh.push_back(glm::vec2(size.x, -size.y));
	m_Mesh.push_back(glm::vec2(1.0f, 0.0f));

	m_Mesh.push_back(glm::vec2(size.x, size.y));
	m_Mesh.push_back(glm::vec2(1.0f, 1.0f));

	m_Mesh.push_back(glm::vec2(-size.x, size.y));
	m_Mesh.push_back(glm::vec2(0.0f, 1.0f));

	m_Vao = new VertexArrayObj();
	m_Layout = new VertexBufferLayout();
	m_Vbo = new VertexBufferObj(m_Mesh.data(), m_Mesh.size() * 2 * VertexBufferObjElement::getSizeOfType(GL_FLOAT));
	m_Layout->push<float>(2); // vertices positions
	m_Layout->push<float>(2); // texCoords
	m_Vao->addVertexBufferObj(*m_Vbo, *m_Layout);

	Position = glm::vec2(size.x, size.y);


	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_Ibo = new IndexBufferObj(indices, 6);
}
