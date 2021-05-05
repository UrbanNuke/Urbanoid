#pragma once
#include <vector>

#include "gameObjects/brick.h"

class GameLevel {
	enum class BrickColor {
		Red = 1,
		Green,
		BlueLight,
		Yellow,
		Pink
	};
	
	std::vector<Brick*> m_Bricks;
	unsigned int m_Grade;
	unsigned int m_BricksLeft;
	
	unsigned int m_OffsetFromTop; // in lines
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;

	std::vector<std::vector<unsigned int>> m_Data;

private:
	glm::vec4 getBrickColor(const BrickColor color) const;
	
public:
	GameLevel(const unsigned int level, const unsigned int width, const unsigned int height);
	~GameLevel();
	
	void generateBricks();
	void destroyBrick(const Brick* brick);

	inline const std::vector<Brick*>& getBricks() const { return m_Bricks; };
	inline unsigned int getGrade() const { return m_Grade; };
	inline unsigned int bricksLeft() const { return m_BricksLeft; }
};
