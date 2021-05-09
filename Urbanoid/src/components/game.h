#pragma once
#include "gameLevel.h"
#include "../../projectResources.h"
#include "../audio/audioEngine.h"
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
	AudioEngine* m_AudioEngine;
	GameObject* m_Background;
	GameObject* m_Overlay;
	Paddle* m_Paddle;
	GameLevel* m_Level;
	Ball* m_Ball;
	std::vector<Text*> m_MainMenu;
	std::vector<Text*> m_WinScreen;
	std::vector<Text*> m_LoseScreen;

	std::vector<GameObject*> m_PlayerLives;

	unsigned int m_MaxPlayerLives = 3;
	unsigned int m_CurrentLevel = 1;
	std::array<unsigned int, 4> m_Levels {
		0, LEVEL_1, LEVEL_2, LEVEL_3
	};
	std::array<std::string, 4> m_Backgrounds {
		"main_menu_bg", "level1_bg", "level2_bg", "level3_bg"
	};
	std::array<std::string, 4> m_BackgroundMusics {
		"main_menu_music", "level1_music", "level2_music", "level3_music"
	};
	unsigned int m_ScreenWidth, m_ScreenHeight;

	bool Keys[1024];
	bool KeysProcessed[1024];
private:

	struct Collision {
		bool occurred;
		Utils::Direction side;
		glm::vec2 diff;
	};

	void generatePlayerLives();
	void createMenus();
	void paddleMovement(const float dt) const;
	void checkBallWallCollision() const;
	void checkBallBricksCollision() const;
	Collision checkBallCollision(GameObject* other) const;
	void restart();

public:
	GameState State;

	Game(const unsigned int width, const unsigned int height);
	~Game();

	void init();

	void input(const float dt);
	void update(const float dt);
	void collisionCheck() const;
	void render() const;

	inline const Renderer* getRenderer() const { return m_Renderer; }

	inline void keyDown(const int key) { Keys[key] = true; }
	inline void keyUp(const int key) {
		Keys[key] = false;
		KeysProcessed[key] = false;
	}
	inline bool getKeyDown(const int key) const { return Keys[key]; }
	inline bool getKeyUp(const int key) const { return !Keys[key]; }
	inline bool getKeyPressed(const int key) const {
		return Keys[key] && !KeysProcessed[key];
	}
	inline void processKey(const int key) { KeysProcessed[key] = true; }
};
