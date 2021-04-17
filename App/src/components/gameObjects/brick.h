﻿#pragma once
#include "gameObject.h"

class Brick final : public GameObject {
	
public:
	Brick(const glm::vec2& position, const glm::vec2& size, const std::string& texture, const std::string& shader);
	~Brick() override;


	void move(const float dt) override;
};