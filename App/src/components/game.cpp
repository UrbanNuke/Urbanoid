#include "game.h"

#include <GLFW/glfw3.h>

#include "gameLevel.h"
#include "../../projectResources.h"
#include "../openGL/renderer.h"
#include "gameObjects/paddle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(const unsigned int width, const unsigned int height)
	: m_Renderer(nullptr),
	  m_Background(nullptr),
	  m_Level(nullptr),
	  m_Ball(nullptr),
	  m_ScreenWidth(width),
	  m_ScreenHeight(height),
	  Keys(),
	  State(GameState::Game)
{
	m_Background = new GameObject(
		glm::vec2(0.0f, 0.0f),
		glm::vec2(static_cast<float>(width), static_cast<float>(height)),
		"background",
		"basic"
	);

	const float paddleSizeX = 50.0f;
	const float paddleSizeY = 10.0f;
	const float offsetPaddleBottom = 30.0f;

	const float ballRadius = 7.0f;
	const float ballPosX = width / 2 + ballRadius;
	const float ballPosY = paddleSizeY + offsetPaddleBottom + ballRadius;
	
	m_Paddle = new Paddle(
		glm::vec2(width / 2, offsetPaddleBottom), 
		glm::vec2(paddleSizeX, paddleSizeY), 
		"paddle", 
		"basic"
	);
	m_Ball = new Ball(
		glm::vec2(ballPosX, ballPosY), 
		glm::vec2(ballRadius, ballRadius), 
		"ball", 
		"basic"
	);
}

Game::~Game() {
	delete m_Renderer;
	delete m_Background;
	delete m_Paddle;
}

void Game::init() {
	m_Renderer = new Renderer(m_ScreenWidth, m_ScreenHeight);
	ResourceManager::loadShader(BASIC_SHADER, "basic");
	ResourceManager::loadTexture2D(BACKGROUND, "background");
	ResourceManager::loadTexture2D(PADDLE, "paddle");
	ResourceManager::loadTexture2D(BRICK, "brick");
	ResourceManager::loadTexture2D(BALL, "ball");
	m_Level = new GameLevel(m_Levels[1], 1, m_ScreenWidth, m_ScreenHeight);
	m_Level->generateBricks();
}

void Game::paddleMovement(const float dt) const {
	if ((getKeyUp(GLFW_KEY_A) || getKeyDown(GLFW_KEY_LEFT))
		&& (getKeyUp(GLFW_KEY_D) || getKeyDown(GLFW_KEY_RIGHT))) {
		m_Paddle->Velocity = Paddle::START_VELOCITY;
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

		if (getKeyDown(GLFW_KEY_SPACE)) {
			m_Ball->unstuck();
		}
	}
}

void Game::update(const float dt) const {
	if (State == GameState::Game) {
		if (!m_Ball->isStack()) {
			// move ball
			m_Ball->move(dt * static_cast<float>(m_ScreenHeight));
		} else {
			m_Ball->Position.x = m_Paddle->Position.x + m_Ball->Size.x;
		}
	}
}

void Game::collisionCheck() const {
	
	// check ball & borders collisions
	if (m_Ball->Position.x + m_Ball->Size.x >= m_ScreenWidth) {
		m_Ball->Velocity.x = -m_Ball->Velocity.x;
		m_Ball->Position.x = m_ScreenWidth - m_Ball->Size.x;
	}

	if (m_Ball->Position.x - m_Ball->Size.x <= 0.0f) {
		m_Ball->Velocity.x = -m_Ball->Velocity.x;
		m_Ball->Position.x = 0.0f + m_Ball->Size.x;
	}

	if (m_Ball->Position.y + m_Ball->Size.y >= m_ScreenHeight) {
		m_Ball->Velocity.y = -m_Ball->Velocity.y;
		m_Ball->Position.y = m_ScreenHeight - m_Ball->Size.y;
	}
}

void Game::render() const {
	m_Renderer->draw(*m_Background);
	m_Renderer->draw(*m_Paddle);
	m_Renderer->draw(m_Level->getBricks());
	m_Renderer->draw(*m_Ball);
}
