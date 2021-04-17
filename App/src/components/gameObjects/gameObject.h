#pragma once
#include <vector>

#include "../../managers/resourceManager.h"
#include "../../openGL/indexBufferObj.h"
#include "../../openGL/shader.h"
#include "../../openGL/vertexArrayObj.h"
#include "../../openGL/vertexBufferLayout.h"
#include "../../openGL/vertexBufferObj.h"
#include "glm/vec2.hpp"

class GameObject {
protected:
	enum class Shape {
		None = -1,
		Brick
	};

	VertexArrayObj* m_Vao;
	VertexBufferObj* m_Vbo;
	VertexBufferLayout* m_Layout;
	IndexBufferObj* m_Ibo;

	std::vector<glm::vec2> m_Mesh;

	Shape m_Type;

	std::string m_ShaderName;
	std::string m_TextureName;

protected:
	virtual void createMesh();

public:
	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;

	GameObject(const glm::vec2& position,
	           const glm::vec2& size,
	           const std::string& texture,
	           const std::string& shader,
	           const glm::vec4& color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	);
	virtual ~GameObject();

	virtual void move(const float dt) {
	};

	inline const void* getMeshData() const { return m_Mesh.data(); }
	inline const VertexArrayObj* getVAO() const { return m_Vao; }
	inline const VertexBufferObj* getVBO() const { return m_Vbo; }
	inline const IndexBufferObj* getIBO() const { return m_Ibo; }
	inline const VertexBufferLayout* getLayout() const { return m_Layout; }
	inline Shader* getShader() const { return ResourceManager::getShader(m_ShaderName); }
	inline Texture2D* getTexture2D() const { return ResourceManager::getTexture2D(m_TextureName); }
};
