﻿#include "ball.h"

Ball::Ball(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader)
	: GameObject(position, size, texture, shader), m_IsStuck(true), m_StartPosition(position), Velocity(glm::vec2(1.0f, 1.0f))
{
	Velocity *= START_VELOCITY;
}


Ball::~Ball() {
}

void Ball::move(const float dt) {
	Position += dt * Velocity;
}

void Ball::resetPosition() {
	Position = m_StartPosition;
	m_IsStuck = true;
}
