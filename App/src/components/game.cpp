#include "game.h"

#include "../../projectResources.h"
#include "../openGL/renderer.h"
#include "gameObjects/brick.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(const unsigned int width, const unsigned int height)
	:	m_Renderer(nullptr),
		m_Brick(nullptr), m_Brick2(nullptr),
		m_Width(width),
		m_Height(height),
		State(GameState::MainMenu),
		Keys()
{
	m_Brick = new Brick(glm::vec2(0.005f, -0.005f), "sample_texture", "basic", glm::vec2(100.0f, 100.0f));
	m_Brick2 = new Brick(glm::vec2(-0.005f, 0.005f), "sample_texture", "basic", glm::vec2(50.2f, 50.2f));
}

Game::~Game() {
}

void Game::init() {
	m_Renderer = new Renderer(m_Width, m_Height);
	ResourceManager::loadShader(BASIC_SHADER, "basic");
	ResourceManager::loadTexture2D(SAMPLE_TEXTURE, "sample_texture");
}

void Game::input() const {
	
}

void Game::update() const {
	m_Brick->Move(1.005f);
	m_Brick2->Move(-1.005f);
}

void Game::collisionCheck() const {
}

void Game::render() const {
	m_Renderer->draw(*m_Brick);
	//m_Renderer->draw(*m_Brick2);
}
