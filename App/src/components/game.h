#pragma once


class Game {
	enum GameState {
		Active,
		MainMenu,
		WinScreen,
		LooseScreen
	};

public:
	GameState m_State;
	bool m_Keys[1024];

	Game();
	~Game();

	void init();

	void input();
	void update();
	void collisionCheck();
	void render();
};


