#include "Game.h"

#include "Collision.h"
#include "Utils.h"

#include <irrKlang/irrKlang.h>
#include <spdlog/spdlog.h>

Game::Game(int width, int height)
	: m_WindowWidth(width), m_WindowHeight(height) {
	// Create subsystems
	m_RenderSystem = new RenderSystem;
	m_InputSystem = new InputSystem;
	m_ScoreSystem = new ScoreSystem;
	m_SoundSystem = new SoundSystem;
}

void Game::Init() {
	// Initialize subsystems
	m_RenderSystem->SetWidth(m_WindowWidth);
	m_RenderSystem->SetHeight(m_WindowHeight);
	m_RenderSystem->Init();
	m_InputSystem->Init();
	m_InputSystem->SetWindow(m_RenderSystem->GetWindow());
	m_ScoreSystem->Init();
	m_SoundSystem->Init();

	// Create players
	glm::vec2 playerSize = glm::vec2(20.0f, 100.0f);
	m_Player1 = new Player(glm::vec2(-m_WindowWidth / 2 + 100.0f, 0.0f), playerSize, 1);
	m_Player2 = new Player(glm::vec2( m_WindowWidth / 2 - 100.0f, 0.0f), playerSize, 2);

	// Create ball
	glm::vec2 ballPosition = glm::vec2(0.0f);
	glm::vec2 ballSize = glm::vec2(25.0f, 25.0f);
	m_Ball = new Ball(ballPosition, ballSize);

	// Create background
	Texture background("Textures/background.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	m_Background = new Quad(glm::vec2(0.0f), glm::vec2(m_WindowWidth, m_WindowHeight), background);

	m_Camera = m_RenderSystem->GetCamera();
}

void Game::Run() {
	Shader shader = *m_RenderSystem->GetShader();
	GLFWwindow* window = m_RenderSystem->GetWindow();

	double prevTime = 0;
	while (m_IsRunning) {
		double currTime = glfwGetTime();
		double delta = currTime - prevTime;
		prevTime = currTime;

		m_RenderSystem->Render();

		// Handle window closing
		if (m_InputSystem->KeyDown(GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window)) {
			m_IsRunning = false;
		}

		// Update players input and ball movement
		m_Player1->Input((float)m_WindowHeight, *m_InputSystem, delta);
		m_Player2->Input((float)m_WindowHeight, *m_InputSystem, delta);
		m_Ball->Move(glm::vec2(m_WindowWidth, m_WindowHeight), delta);

		// Handle ball collision with players
		if (BallPlayerCollision(m_Ball->GetAABB(), m_Player1->GetAABB())) {
			glm::vec2 dir = glm::vec2(1.0f, Random::Float(-1.0f, 1.0f));
		    dir = glm::normalize(dir);
		    m_Ball->SetDirection(dir);
			m_SoundSystem->PlaySound(m_SoundSystem->blip);
		}
		else if (BallPlayerCollision(m_Ball->GetAABB(), m_Player2->GetAABB())) {
			glm::vec2 dir = glm::vec2(-1.0f, Random::Float(-1.0f, 1.0f));
		    dir = glm::normalize(dir);
			m_Ball->SetDirection(dir);
			m_SoundSystem->PlaySound(m_SoundSystem->blip);
		}

		// Handle scoring
		if (m_Ball->GetPosition().x + m_Ball->GetSize().x > (float)m_WindowWidth / 2) {
			m_ScoreSystem->AddScore(1);
			m_Ball->SetPosition(glm::vec2(0.0f));
			glm::vec2 dir = Random::Vec2(-1.0f, 1.0f);
			m_Ball->SetDirection(dir);
			m_SoundSystem->PlaySound(m_SoundSystem->score);
		}
		else if (m_Ball->GetPosition().x - m_Ball->GetSize().x < - (float)m_WindowWidth / 2) {
			m_ScoreSystem->AddScore(2);
			m_Ball->SetPosition(glm::vec2(0.0f));
			glm::vec2 dir = Random::Vec2(-1.0f, 1.0f);
			m_Ball->SetDirection(dir);
			m_SoundSystem->PlaySound(m_SoundSystem->score);
		}

		// Draw sprites
		m_Background->Draw(shader, *m_Camera);
		m_Player1->Draw(shader, *m_Camera);
		m_Player2->Draw(shader, *m_Camera);
		m_Ball->Draw(shader, *m_Camera);

		glfwSwapBuffers(window);
		m_InputSystem->Update();
	}
}

void Game::Close() {
	spdlog::info("Game Closing!");
	m_ScoreSystem->Close();
	m_InputSystem->Close();
	m_RenderSystem->Close();
}