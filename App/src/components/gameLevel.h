#pragma once
#include <vector>

#include "gameObjects/brick.h"

class GameLevel {
	std::vector<Brick*> m_Bricks;
	unsigned int m_Grade;
public:
	GameLevel(const unsigned int level);
	~GameLevel();

	inline const std::vector<Brick*>& getBricks() const { return m_Bricks; };
	inline unsigned int getGrade() const { return m_Grade; };
};
