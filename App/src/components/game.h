#pragma once
#include "../openGL/renderer.h"
#include "gameObjects/paddle.h"


class Game {
	enum class GameState {
		MainMenu,
		Game,
		WinScreen,
		LooseScreen
	};

	Renderer* m_Renderer;
	GameObject* m_Brick;
	GameObject* m_Brick2;
	GameObject* m_Background;
	Paddle* m_Paddle;

	unsigned int m_ScreenWidth, m_ScreenHeight;

	bool Keys[1024];
private:
	void paddleMovement(const float dt) const;

public:
	GameState State;

	Game(const unsigned int width, const unsigned int height);
	~Game();

	void init();

	void input(const float dt) const;
	void update() const;
	void collisionCheck() const;
	void render() const;

	inline const Renderer* getRenderer() const { return m_Renderer; }

	inline void keyDown(const int key) { Keys[key] = true; }
	inline void keyUp(const int key) { Keys[key] = false; }
	inline bool getKeyDown(const int key) const { return Keys[key]; }
	inline bool getKeyUp(const int key) const { return !Keys[key]; }
};


