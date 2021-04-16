#pragma once
#include "../openGL/renderer.h"


class Game {
	enum class GameState {
		Active,
		MainMenu,
		WinScreen,
		LooseScreen
	};

	Renderer* m_Renderer;
	GameObject* m_Brick;
	GameObject* m_Brick2;

	unsigned int m_Width, m_Height;

public:
	GameState State;
	bool Keys[1024];

	Game(const unsigned int width, const unsigned int height);
	~Game();

	void init();

	void input() const;
	void update() const;
	void collisionCheck() const;
	void render() const;

	inline const Renderer* getRenderer() const { return m_Renderer; }
};


