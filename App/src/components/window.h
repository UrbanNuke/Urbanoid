#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"

class Window {
	GLFWwindow* m_Window;
	Game* m_Game;
	
public:
	Window(const std::string& windowName, const unsigned int width, const unsigned int height);
	~Window();

	inline GLFWwindow* getWindowPointer() const { return m_Window; }
	void launchGameLoop(Game& game);
};

