#pragma once
#include "gameObject.h"

class Ball final : public GameObject {

	inline static float START_VELOCITY = 0.5f;
	inline static float MAX_VELOCITY = 2.0f;
	
	bool m_IsStuck;

	glm::vec2 m_StartPosition;

public:
	glm::vec2 Velocity;
	
	Ball(const glm::vec2& position,
	     const glm::vec2& size,
	     const std::string& texture,
	     const std::string& shader);
	~Ball() override;

	inline bool isStack() const { return m_IsStuck; }
	inline void unstuck() { m_IsStuck = false; }
	void move(const float dt) override;
	void resetPosition();
};
