#include "gameLevel.h"

#include <sstream>
#include <string>

#include "../../res/resource.h"

GameLevel::GameLevel(const unsigned int level, const unsigned int grade, const unsigned int width, const unsigned int height)
	: m_Bricks(std::vector<GameObject*>{}),
	  m_Grade(grade),
	  m_OffsetFromTop(0),
	  m_ScreenWidth(width),
	  m_ScreenHeight(height),
	  m_Data(std::vector<std::vector<unsigned int>>{}) {
	Resource res = Resource(level, "LEVEL");
	std::stringstream ss[2];
	ss[0] << res.GetResourceString();

	unsigned int ch;

	std::string line;
	int i = 0;
	while (getline(ss[0], line)) {

		ss[1].str(line);
		ss[1].clear();
		if (i == 0) {
			++i;
			ss[1] >> m_OffsetFromTop;
			continue;
		}

		m_Data.push_back(std::vector<unsigned int>{});
		while (ss[1] >> ch) {
			m_Data[m_Data.size() - 1].push_back(ch);
		}

	}
}

GameLevel::~GameLevel() {
}

void GameLevel::generateBricks() {
	const float brickSize = static_cast<float>(m_ScreenWidth / m_Data[0].size());
	// size one side from center
	const float sizeX = brickSize / 2; 
	const float sizeY = brickSize / 5;
	auto posY = static_cast<float>(m_ScreenHeight - m_OffsetFromTop * sizeY * 2);
	
	for (auto row : m_Data) {


		float posX = 0.0f;
		
		for (const unsigned int brickType : row) {

			if (brickType == 0) {
				posX += sizeX * 2;
				continue;
			}
			
			m_Bricks.push_back(
				new Brick(
					glm::vec2(posX + sizeX, posY + sizeY),
					glm::vec2(sizeX, sizeY),
					"brick",
					"basic",
					getBrickColor(static_cast<BrickColor>(brickType))
				)
			);
			m_Bricks[m_Bricks.size() - 1]->createMesh();
			
			posX += sizeX * 2;
		}
		
		posY -= sizeY * 2;
	}
}

void GameLevel::destroyBrick(const GameObject* objPtr) {
	const auto ptr = std::find(m_Bricks.begin(), m_Bricks.end(), objPtr);
	if (ptr == m_Bricks.end()) {
		std::cerr << "Brick wasn't found on the playground" << std::endl;
		return;
	}
	m_Bricks.erase(ptr);
	delete objPtr;
}

glm::vec4 GameLevel::getBrickColor(const BrickColor color) const {
	switch (color) {
		case BrickColor::Red:
			return ResourceManager::s_RedColor;
		case BrickColor::Green:
			return ResourceManager::s_GreenColor;
		case BrickColor::BlueLight:
			return ResourceManager::s_LightBlueColor;
		case BrickColor::Yellow:
			return ResourceManager::s_YellowColor;
		case BrickColor::Pink:
			return ResourceManager::s_PinkColor;
		default:
			return ResourceManager::s_RedColor;
	}
}
