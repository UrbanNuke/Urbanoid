#pragma once
#include "gameObject.h"

class Brick : public GameObject {
	
public:
	Brick(const glm::vec2& position, const std::string& texture, const std::string& shader, const glm::vec2& size);
	~Brick() override;

private:
	void createMesh(const glm::vec2& size) override;
};
