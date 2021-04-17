#include "game.h"

#include <GLFW/glfw3.h>
#include "../../projectResources.h"
#include "../openGL/renderer.h"
#include "gameObjects/brick.h"
#include "gameObjects/paddle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(const unsigned int width, const unsigned int height)
	: m_Renderer(nullptr),
	  m_Brick(nullptr), m_Background(nullptr),
	  m_ScreenWidth(width),
	  m_ScreenHeight(height),
	  Keys(),
	  State(GameState::Game) {
	m_Brick = new Brick(glm::vec2(0.005f, -0.005f), glm::vec2(25.0f, 10.0f), 
		"brick", "basic", glm::vec4(0.3f, 0.2f, 0.5f, 1.0f));
	m_Background = new GameObject(
		glm::vec2(0.0f, 0.0f),
		glm::vec2(static_cast<float>(width), static_cast<float>(height)),
		"background",
		"basic"
	);
	m_Paddle = new Paddle(glm::vec2(width / 2, 30.0f), glm::vec2(50.0f, 10.0f), "paddle", "basic");
}

Game::~Game() {
	delete m_Renderer;
	delete m_Brick;
	delete m_Background;
	delete m_Paddle;
}

void Game::init() {
	m_Renderer = new Renderer(m_ScreenWidth, m_ScreenHeight);
	ResourceManager::loadShader(BASIC_SHADER, "basic");
	ResourceManager::loadTexture2D(BACKGROUND, "background");
	ResourceManager::loadTexture2D(PADDLE, "paddle");
	ResourceManager::loadTexture2D(BRICK, "brick");
}

void Game::paddleMovement(const float dt) const {
	if ((getKeyUp(GLFW_KEY_A) || getKeyDown(GLFW_KEY_LEFT))
		&& (getKeyUp(GLFW_KEY_D) || getKeyDown(GLFW_KEY_RIGHT))) 
	{
		m_Paddle->Velocity = Paddle::START_PADDLE_VELOCITY;
	}
	if (getKeyDown(GLFW_KEY_A) || getKeyDown(GLFW_KEY_LEFT)) {
		const float paddleDt = m_Paddle->Velocity * dt * m_ScreenWidth;
		if (m_Paddle->Position.x - m_Paddle->Size.x - paddleDt <= 1) {
			return;
		}
		m_Paddle->move(-paddleDt);
		m_Paddle->increaseVelocity(0.015f);
	}
	if (getKeyDown(GLFW_KEY_D) || getKeyDown(GLFW_KEY_RIGHT)) {
		const float paddleDt = m_Paddle->Velocity * dt * m_ScreenWidth;
		if (m_Paddle->Position.x + m_Paddle->Size.x + paddleDt >= m_ScreenWidth) {
			return;
		}
		m_Paddle->move(paddleDt);
		m_Paddle->increaseVelocity(0.015f);
	}
}

void Game::input(const float dt) const {
	if (State == GameState::Game) {
		paddleMovement(dt);
	}
}

void Game::update() const {
	m_Brick->move(1.005f);
}

void Game::collisionCheck() const {
}

void Game::render() const {
	m_Renderer->draw(*m_Background);
	m_Renderer->draw(*m_Brick);
	m_Renderer->draw(*m_Paddle);
}
