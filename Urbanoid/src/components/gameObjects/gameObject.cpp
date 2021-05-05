#include "gameObject.h"

#include <GL/glew.h>
#include "../../openGL/vertexBufferLayout.h"

GameObject::GameObject(
	const glm::vec2& position,
	const glm::vec2& size,
	const std::string& texture,
	const std::string& shader,
	const glm::vec4& color)
	: m_Vao(nullptr),
	  m_Vbo(nullptr),
	  m_Layout(nullptr),
	  m_Ibo(nullptr),
	  m_Mesh(std::vector<glm::vec2>()),
	  m_Type(Shape::None),
	  m_ShaderName(shader),
	  m_TextureName(texture),
	  Position(position),
	  Size(size),
	  Color(color)
{
}

void GameObject::createMesh() {
	// creating basic square
	// first pair - vertex, second - texture
	m_Mesh.push_back(glm::vec2(-Size.x, -Size.y));
	m_Mesh.push_back(glm::vec2(0.0f, 0.0f));

	m_Mesh.push_back(glm::vec2(Size.x, -Size.y));
	m_Mesh.push_back(glm::vec2(1.0f, 0.0f));

	m_Mesh.push_back(glm::vec2(Size.x, Size.y));
	m_Mesh.push_back(glm::vec2(1.0f, 1.0f));

	m_Mesh.push_back(glm::vec2(-Size.x, Size.y));
	m_Mesh.push_back(glm::vec2(0.0f, 1.0f));

	m_Vao = new VertexArrayObj();
	m_Layout = new VertexBufferLayout();
	m_Vbo = new VertexBufferObj(m_Mesh.data(), m_Mesh.size() * 2 * VertexBufferObjElement::getSizeOfType(GL_FLOAT));
	m_Layout->push<float>(2); // vertices positions
	m_Layout->push<float>(2); // texCoords
	m_Vao->addVertexBufferObj(*m_Vbo, *m_Layout);


	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	m_Ibo = new IndexBufferObj(indices, 6);
}

GameObject::~GameObject() {
	delete m_Vao;
	delete m_Vbo;
	delete m_Layout;
	delete m_Ibo;
}
