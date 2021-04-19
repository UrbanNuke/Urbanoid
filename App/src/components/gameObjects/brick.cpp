﻿#include "brick.h"

Brick::Brick(const glm::vec2& position,
             const glm::vec2& size,
             const std::string& texture,
             const std::string& shader,
             const glm::vec4& color
): GameObject(position, size, texture, shader, color) {
	m_Type = Shape::Brick;
}

Brick::~Brick() {
}
