#pragma once
#include "gameObject.h"

class Paddle final : public GameObject {
	glm::vec2 m_StartPosition;
	
public:
	inline static float START_PADDLE_VELOCITY = 0.5f;
	inline static float MAX_PADDLE_VELOCITY = 1.0f;

	float Velocity;
	
	Paddle(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader);
	~Paddle() override;
	
	void move(const float dt) override;
	void resetPosition();
	void increaseVelocity(const float dt);
};
