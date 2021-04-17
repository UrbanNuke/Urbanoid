#pragma once
#include "gameObject.h"

class Paddle final : public GameObject {
public:
	Paddle(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader);
	~Paddle() override;
	
	void move(const float dt) override;
	void resetPosition();

};
