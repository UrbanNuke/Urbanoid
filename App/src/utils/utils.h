#pragma once
#include <array>

#include "glm/vec2.hpp"

namespace Utils {
	enum class Direction {
		Up,
		Right,
		Down,
		Left
	};

	inline std::array<glm::vec2, 4> compass {
		glm::vec2(0.0f, 1.0f), // up
		glm::vec2(1.0f, 0.0f), // right
		glm::vec2(0.0f, -1.0f), // down
		glm::vec2(-1.0f, 0.0f) // left
	};

	Direction getDirection(const glm::vec2 source);
}

