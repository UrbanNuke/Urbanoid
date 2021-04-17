#include "paddle.h"

Paddle::Paddle(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader)
	: GameObject(position, size, texture, shader)
{
	
}

Paddle::~Paddle() {
	
}

void Paddle::move(const float dt) {
	
}

void Paddle::resetPosition() {
	
}
