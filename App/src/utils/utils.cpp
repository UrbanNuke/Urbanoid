#include "utils.h"


#include <iostream>


#include "glm/geometric.hpp"

namespace Utils {
	
	Direction getDirection(const glm::vec2 source) {
		const glm::vec2 sourceNormalized = glm::normalize(source);

		float max = 0.0f;
		int bestMatch = 0;
		for (unsigned int i = 0; i < compass.size() - 1; ++i) {
			const float dot = glm::dot(sourceNormalized, compass[i]);
			std::cout << "DOT: " << dot << std::endl;
			if (dot > max) {
				
				max = dot;
				bestMatch = i;
			}
		}

		std::cout << "MAX: " << max << std::endl;
		std::cout << "bestMatch: " << bestMatch << std::endl;

		return static_cast<Direction>(bestMatch);
	}
	
}

