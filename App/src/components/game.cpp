#include "game.h"

#include "../../projectResources.h"
#include "../openGL/renderer.h"
#include "gameObjects/brick.h"

Game::Game() : m_Renderer(nullptr), m_Brick(nullptr), m_Brick2(nullptr), State(GameState::MainMenu), Keys{ false } {
	m_Brick = new Brick(glm::vec2(0.005f, -0.005f), "sample_texture", "basic", glm::vec2(0.5f, 0.5f));
	m_Brick2 = new Brick(glm::vec2(-0.005f, 0.005f), "sample_texture", "basic", glm::vec2(0.2f, 0.2f));
}

Game::~Game() {
}

void Game::init() {
	ResourceManager::loadShader(BASIC_SHADER, "basic");
	ResourceManager::loadTexture2D(SAMPLE_TEXTURE, "sample_texture");
	m_Renderer = new Renderer();
}

void Game::input() const {
	
}

void Game::update() const {
	m_Brick->Move(0.005f);
	m_Brick2->Move(-0.005f);
}

void Game::collisionCheck() const {
}

void Game::render() const {
	m_Renderer->draw(*m_Brick);
	m_Renderer->draw(*m_Brick2);
}
