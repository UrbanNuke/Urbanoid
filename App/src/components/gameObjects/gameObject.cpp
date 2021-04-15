#include "gameObject.h"

#include "../../openGL/vertexBufferLayout.h"

void GameObject::createMesh(const glm::vec2& size) {
}

GameObject::GameObject(const glm::vec2& position, const std::string& texture, const std::string& shader)
	:	m_Vao(nullptr),
		m_Vbo(nullptr),
		m_Layout(nullptr),
		m_Ibo(nullptr),
		m_Mesh(std::vector<glm::vec2>()),
		m_Type(Shape::None),
		m_ShaderName(shader),
		m_TextureName(texture),
		Position(position)
{
	
}

GameObject::~GameObject() {
	delete m_Vao;
	delete m_Vbo;
	delete m_Layout;
	delete m_Ibo;
}

void GameObject::Move(float dt) {
	Position.x += dt;
	Position.y += dt;
}
