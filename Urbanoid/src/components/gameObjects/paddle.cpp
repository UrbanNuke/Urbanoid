#include "paddle.h"

Paddle::Paddle(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader)
	: GameObject(position, size, texture, shader), m_StartPosition(position), Velocity(START_VELOCITY)
{
	
}

Paddle::~Paddle() {
	
}

void Paddle::move(const float dt) {
	Position.x += dt;
}

void Paddle::resetPosition() {
	Position = m_StartPosition;
}

void Paddle::increaseVelocity(const float dt) {
	if (Velocity + dt > 1.0f) {
		Velocity = MAX_VELOCITY;
		return;
	}
	Velocity += dt;
}
