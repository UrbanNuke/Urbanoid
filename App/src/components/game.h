#pragma once
#include "gameLevel.h"
#include "../../projectResources.h"
#include "../openGL/renderer.h"
#include "../utils/utils.h"
#include "gameObjects/ball.h"
#include "gameObjects/paddle.h"


class Game {
	enum class GameState {
		MainMenu,
		Game,
		WinScreen,
		LooseScreen
	};

	Renderer* m_Renderer;
	GameObject* m_Background;
	GameObject* m_Overlay;
	Paddle* m_Paddle;
	GameLevel* m_Level;
	Ball* m_Ball;
	std::vector<Text*> m_MainMenu;

	unsigned int m_Levels[2]{ 0, LEVEL_1 };
	unsigned int m_ScreenWidth, m_ScreenHeight;

	bool Keys[1024];
private:

	struct Collision {
		bool occurred;
		Utils::Direction side;
		glm::vec2 diff;
	};

	void createMenus();
	void paddleMovement(const float dt) const;
	void checkBallWallCollision() const;
	void checkBallBricksCollision() const;
	Collision checkBallCollision(GameObject* other) const;

public:
	GameState State;

	Game(const unsigned int width, const unsigned int height);
	~Game();

	void init();

	void input(const float dt);
	void update(const float dt) const;
	void collisionCheck() const;
	void render();

	inline const Renderer* getRenderer() const { return m_Renderer; }

	inline void keyDown(const int key) { Keys[key] = true; }
	inline void keyUp(const int key) { Keys[key] = false; }
	inline bool getKeyDown(const int key) const { return Keys[key]; }
	inline bool getKeyUp(const int key) const { return !Keys[key]; }
};


