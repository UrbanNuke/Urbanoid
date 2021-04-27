#pragma once
#include "gameObject.h"

class Text final : public GameObject {
	std::string m_Text;

public:
	void createMesh() override;
	Text(const std::string& text,
	     const glm::vec2& position,
	     const glm::vec2& size,
	     const std::string& shader);
	~Text() override;

	inline const std::string& getText() const { return m_Text; }
};
