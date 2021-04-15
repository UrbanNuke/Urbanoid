#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.h"

class Window {
	GLFWwindow* m_Window;
	Game* m_Game;

	
public:
	unsigned int Width, Height;
	
	Window(const std::string& windowName, const unsigned int width, const unsigned int height);
	~Window();

	void launchGameLoop() const;
};

