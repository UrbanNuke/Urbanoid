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
	
	std::vector<GameObject*> m_Bricks;
	unsigned int m_Grade;
	
	unsigned int m_OffsetFromTop; // in lines
	unsigned int m_ScreenWidth;
	unsigned int m_ScreenHeight;

	std::vector<std::vector<unsigned int>> m_Data;

private:
	glm::vec4 getBrickColor(const BrickColor color) const;
	
public:
	GameLevel(const unsigned int level, const unsigned int grade, const unsigned int width, const unsigned int height);
	~GameLevel();
	
	void generateBricks();

	inline const std::vector<GameObject*>& getBricks() const { return m_Bricks; };
	inline unsigned int getGrade() const { return m_Grade; };
};
