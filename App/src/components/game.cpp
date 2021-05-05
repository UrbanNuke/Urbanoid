/*
 * Urbanoid by Alexander Urbanyk.
 * 
 * Game process is described here.
 * Init -> User Input -> Update -> Check Collisions -> Render
 * main game loop.
 */

#include "game.h"

#include <GLFW/glfw3.h>

#include "gameLevel.h"
#include "../../projectResources.h"
#include "../utils/utils.h"
#include "gameObjects/paddle.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

Game::Game(const unsigned int width, const unsigned int height)
	: m_Renderer(nullptr),
	  m_Background(nullptr),
	  m_Overlay(nullptr),
	  m_Level(nullptr),
	  m_Ball(nullptr),
	  m_ScreenWidth(width),
	  m_ScreenHeight(height),
	  Keys(),
	  State(GameState::MainMenu)
{
	
	m_Background = new GameObject(
		glm::vec2(width / 2, height / 2),
		glm::vec2(width / 2, height / 2),
		m_Backgrounds[0],
		"basic"
	);
	m_Background->createMesh();

	m_Overlay = new GameObject(
		glm::vec2(width / 2, height / 2),
		glm::vec2(width / 2, height / 2),
		"",
		"basic",
		glm::vec4(0.0f, 0.0f, 0.0f, 0.3f)
	);
	m_Overlay->createMesh();

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
	m_Paddle->createMesh();
	
	m_Ball = new Ball(
		glm::vec2(ballPosX, ballPosY),
		glm::vec2(ballRadius, ballRadius),
		"ball",
		"basic"
	);
	m_Ball->createMesh();
}

Game::~Game() {
	delete m_Renderer;
	delete m_Background;
	delete m_Overlay;
	delete m_Paddle;
	delete m_Level;
	delete m_Ball;
}

void Game::init() {
	m_Renderer = new Renderer(m_ScreenWidth, m_ScreenHeight);
	ResourceManager::loadShader(BASIC_SHADER, "basic");
	ResourceManager::loadShader(FONT_SHADER, "font_shader");
	ResourceManager::loadTexture2D(MAIN_MENU_BG, "main_menu_bg");
	ResourceManager::loadTexture2D(LEVEL1_BG, "level1_bg");
	ResourceManager::loadTexture2D(LEVEL2_BG, "level2_bg");
	ResourceManager::loadTexture2D(LEVEL3_BG, "level3_bg");
	ResourceManager::loadTexture2D(PADDLE, "paddle");
	ResourceManager::loadTexture2D(BRICK, "brick");
	ResourceManager::loadTexture2D(BRICK_SOLID, "brick_solid");
	ResourceManager::loadTexture2D(BALL, "ball");
	ResourceManager::loadAudio(BLEEP, "bleep");
	ResourceManager::loadAudio(BLEEP_PADDLE, "bleep_paddle");
	ResourceManager::loadAudio(BORDER_HIT, "border_hit");
	ResourceManager::loadFont(BASE_FONT);
	createMenus();
	m_Level = new GameLevel(m_Levels[m_CurrentLevel], m_ScreenWidth, m_ScreenHeight);
	m_Level->generateBricks();
	generatePlayerLives();
}

void Game::input(const float dt) {
	if (State == GameState::MainMenu) {
		if (getKeyDown(GLFW_KEY_ENTER)) {
			m_Background->changeTexture2D(m_Backgrounds[m_CurrentLevel]);
			State = GameState::Game;
			
		} else if (getKeyDown(GLFW_KEY_ESCAPE)) {
			exit(0);
		}
	}
	
	if (State == GameState::Game) {
		paddleMovement(dt);

		if (getKeyDown(GLFW_KEY_SPACE)) {
			m_Ball->unstuck();
		}
	}

	if (State == GameState::WinScreen || State == GameState::LooseScreen) {
		if (getKeyDown(GLFW_KEY_ENTER)) {
			m_CurrentLevel = 1;
			generatePlayerLives();
			m_Background->changeTexture2D(m_Backgrounds[m_CurrentLevel]);
			m_Paddle->resetPosition();
			m_Ball->resetPosition();
			delete m_Level;
			m_Level = new GameLevel(m_Levels[m_CurrentLevel], m_ScreenWidth, m_ScreenHeight);
			m_Level->generateBricks();
			State = GameState::Game;

		} else if (getKeyDown(GLFW_KEY_ESCAPE)) {
			exit(0);
		}
	}
}

void Game::update(const float dt) {
	if (State == GameState::Game) {
		// checking on empty level
		if (m_Level->bricksLeft() == 0) {
			if (m_Level->getGrade() == m_Levels[m_Levels.size() - 1]) {
				State = GameState::WinScreen;
				return;
			}

			delete m_Level;
			m_Level = new GameLevel(m_Levels[++m_CurrentLevel], m_ScreenWidth, m_ScreenHeight);
			m_Level->generateBricks();
			m_Background->changeTexture2D(m_Backgrounds[m_CurrentLevel]);
			m_Paddle->resetPosition();
			m_Ball->resetPosition();
		}
		
		if (!m_Ball->isStuck()) {
			// move ball
			m_Ball->move(dt * static_cast<float>(m_ScreenHeight));
		} else {
			m_Ball->Position.x = m_Paddle->Position.x + m_Ball->Size.x;
		}

		if (m_Ball->Position.y <= 0.0f) {
			delete m_PlayerLives[m_PlayerLives.size() - 1];
			m_PlayerLives.erase(m_PlayerLives.end() - 1);
			m_Paddle->resetPosition();
			m_Ball->resetPosition();
			if (m_PlayerLives.empty()) {
				State = GameState::LooseScreen;
			}
		}
	}
}

void Game::collisionCheck() const {
	if (State == GameState::Game) {
		checkBallWallCollision();

		checkBallBricksCollision();

		if (!m_Ball->isStuck()) {
			const Collision ballPaddleCollision = checkBallCollision(m_Paddle);
			if (ballPaddleCollision.occurred) {

				const float smoothDamp = 1.8f;

				const glm::vec2 diff = m_Ball->Position - m_Paddle->Position;
				const glm::vec2 normalized = glm::normalize(diff);
				m_Ball->Velocity.x = normalized.x / smoothDamp;
				m_Ball->Velocity.y = std::abs(m_Ball->Velocity.y);

				ResourceManager::getAudio("bleep_paddle")->play2D();
			}
		}
	}
}

void Game::render() const {
	if (State == GameState::MainMenu) {
		m_Renderer->draw(*m_Background);
		m_Renderer->draw(*m_Overlay);
		m_Renderer->drawText(m_MainMenu);
	}
	
	if (State == GameState::Game) {
		m_Renderer->draw(*m_Background);
		m_Renderer->draw(*m_Paddle);
		m_Renderer->draw(m_Level->getBricks());
		m_Renderer->draw(*m_Ball);
		m_Renderer->draw(m_PlayerLives);
	}

	if (State == GameState::WinScreen) {
		m_Renderer->draw(*m_Background);
		m_Renderer->draw(*m_Overlay);
		m_Renderer->drawText(m_WinScreen);
	}

	if (State == GameState::LooseScreen) {
		m_Renderer->draw(*m_Background);
		m_Renderer->draw(*m_Overlay);
		m_Renderer->drawText(m_LoseScreen);
	}
}

void Game::generatePlayerLives() {
	for (unsigned int i = 1; i <= m_MaxPlayerLives; ++i) {
		GameObject* live = new GameObject(
			glm::vec2(35.0f * i, 10.0f), glm::vec2(13.0f, 5.0f), "paddle", "basic"
		);
		live->createMesh();
		m_PlayerLives.push_back(live);
	}
}

void Game::createMenus() {
	Text* title = new Text(
		"urbanoid", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.5), glm::vec2(1.0f, 1.0f), "font_shader"
	);
	title->createMesh();
	
	Text* author = new Text(
		"by Alexander Urbanyk", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.7f), glm::vec2(0.2f, 0.2f), "font_shader"
	);
	author->createMesh();
	
	Text* newGame = new Text(
		"press ENTER to new game", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 2.5f), glm::vec2(0.3f, 0.3f), "font_shader"
	);
	newGame->createMesh();

	Text* exit = new Text(
		"press ESC to exit", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 2.9f), glm::vec2(0.3f, 0.3f), "font_shader"
	);
	exit->createMesh();
	
	m_MainMenu.push_back(title);
	m_MainMenu.push_back(author);
	m_MainMenu.push_back(newGame);
	m_MainMenu.push_back(exit);

	Text* congratulations = new Text(
		"congratulations", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.5), glm::vec2(1.0f, 1.0f), "font_shader"
	);
	congratulations->createMesh();
	
	Text* winDescription = new Text(
		"you are passed the great game", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.7f), glm::vec2(0.3f, 0.3f), "font_shader"
	);
	winDescription->createMesh();

	Text* thanks = new Text(
		"thank you!", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.8f), glm::vec2(0.3f, 0.3f), "font_shader"
	);
	thanks->createMesh();

	m_WinScreen.push_back(congratulations);
	m_WinScreen.push_back(winDescription);
	m_WinScreen.push_back(thanks);
	m_WinScreen.push_back(newGame);
	m_WinScreen.push_back(exit);

	Text* lose = new Text(
		"game over", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.5), glm::vec2(1.0f, 1.0f), "font_shader"
	);
	lose->createMesh();

	Text* loseDescription = new Text(
		"pull yourself together! and try again", glm::vec2(m_ScreenWidth / 2, m_ScreenHeight / 1.7f), glm::vec2(0.3f, 0.3f), "font_shader"
	);
	loseDescription->createMesh();

	m_LoseScreen.push_back(lose);
	m_LoseScreen.push_back(loseDescription);
	m_LoseScreen.push_back(newGame);
	m_LoseScreen.push_back(exit);
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

void Game::checkBallWallCollision() const {
	if (m_Ball->Position.x + m_Ball->Size.x >= m_ScreenWidth) {
		m_Ball->Velocity.x = -m_Ball->Velocity.x;
		m_Ball->Position.x = m_ScreenWidth - m_Ball->Size.x;
		ResourceManager::getAudio("border_hit")->play2D();
	}

	if (m_Ball->Position.x - m_Ball->Size.x <= 0.0f) {
		m_Ball->Velocity.x = -m_Ball->Velocity.x;
		m_Ball->Position.x = 0.0f + m_Ball->Size.x;
		ResourceManager::getAudio("border_hit")->play2D();
	}

	if (m_Ball->Position.y + m_Ball->Size.y >= m_ScreenHeight) {
		m_Ball->Velocity.y = -m_Ball->Velocity.y;
		m_Ball->Position.y = m_ScreenHeight - m_Ball->Size.y;
		ResourceManager::getAudio("border_hit")->play2D();
	}
}

void Game::checkBallBricksCollision() const {
	for (auto brick : m_Level->getBricks()) {
		const Collision collision = checkBallCollision(brick);
		if (collision.occurred) {
			if (brick->isSolid()) {
				ResourceManager::getAudio("bleep_solid")->play2D();
			} else {
				m_Level->destroyBrick(brick);
				ResourceManager::getAudio("bleep")->play2D();
			}

			using namespace Utils;

			// horizontal
			if (collision.side == Direction::Left || collision.side == Direction::Right) {
				m_Ball->Velocity.x = -m_Ball->Velocity.x;

				const float offsetX = m_Ball->Size.x - std::abs(collision.diff.x);
				collision.side == Direction::Left
					? m_Ball->Position.x += offsetX
					: m_Ball->Position.x -= offsetX;

				//vertical
			} else {
				m_Ball->Velocity.y = -m_Ball->Velocity.y;

				const float offsetY = m_Ball->Size.y - std::abs(collision.diff.y);
				collision.side == Direction::Down
					? m_Ball->Position.y -= offsetY
					: m_Ball->Position.y += offsetY;
			}
		}
	}
}

Game::Collision Game::checkBallCollision(GameObject* other) const {
	const glm::vec2 diff = m_Ball->Position - other->Position;

	// little optimization if diff between center points is less than 100.0f
	if (glm::length(diff) < 100.0f) {
		const glm::vec2 halfObject = glm::vec2(other->Size.x, other->Size.y);
		const glm::vec2 clamped = glm::clamp(diff, -halfObject, halfObject);

		const glm::vec2 closestPoint = other->Position + clamped;
		const glm::vec2 diffResult = m_Ball->Position - closestPoint;

		if (glm::length(diffResult) <= m_Ball->Size.x) {
			return {true, Utils::getDirection(diffResult), diffResult};
		}
	}

	return {false, Utils::Direction::Up, glm::vec2(0.0f, 0.0f)};
}
