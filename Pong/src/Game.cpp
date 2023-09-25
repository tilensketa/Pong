#include "Game.h"

#include "Collision.h"

#include <spdlog/spdlog.h>

Game::Game(int width, int height)
	: m_WindowWidth(width), m_WindowHeight(height) {
	m_RenderSystem = new RenderSystem;
	m_RenderSystem->SetWidth(m_WindowWidth);
	m_RenderSystem->SetHeight(m_WindowHeight);
	m_InputSystem = new InputSystem;
	m_ScoreSystem = new ScoreSystem;
}

void Game::Init() {
	m_RenderSystem->Init();
	m_InputSystem->Init();
	m_InputSystem->SetWindow(m_RenderSystem->GetWindow());
	m_ScoreSystem->Init();

	glm::vec2 playerSize = glm::vec2(10.0f, 100.0f);
	m_Player1 = new Player(glm::vec2(-m_WindowWidth / 2 + 100.0f, 0.0f), playerSize, 1);
	m_Player2 = new Player(glm::vec2( m_WindowWidth / 2 - 100.0f, 0.0f), playerSize, 2);
	m_Ball = new Ball(50.0f, 50.0f, 0.0f, 0.0f);
	Texture background("Textures/background.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	m_Background = new Quad(glm::vec2(0.0f), glm::vec2(m_WindowWidth, m_WindowHeight), background);
	m_Camera = m_RenderSystem->GetCamera();
}

void Game::Run() {
	double prevTime = 0;
	Shader shader = *m_RenderSystem->GetShader();
	GLFWwindow* window = m_RenderSystem->GetWindow();
	while (m_IsRunning) {
		double currTime = glfwGetTime();
		double delta = currTime - prevTime;
		prevTime = currTime;

		m_RenderSystem->Render();
		if (m_InputSystem->KeyDown(GLFW_KEY_ESCAPE)) {
			m_IsRunning = false;
		}

		m_Player1->Input(m_WindowHeight, *m_InputSystem, delta);
		m_Player2->Input(m_WindowHeight, *m_InputSystem, delta);
		m_Ball->Move(glm::vec2(m_WindowWidth, m_WindowHeight), delta);

		if (BallPlayerCollision(m_Ball->GetAABB(), m_Player1->GetAABB())) {
		    float x = std::rand();
		    float y = std::rand();
		    glm::vec2 dir = glm::vec2(x, y);
		    dir = glm::normalize(dir);
		    m_Ball->SetDirection(dir.x, dir.y);
		}
		else if (BallPlayerCollision(m_Ball->GetAABB(), m_Player2->GetAABB())) {
		    float x = std::rand();
		    float y = std::rand();
		    glm::vec2 dir = glm::vec2(-x, y);
		    dir = glm::normalize(dir);
			m_Ball->SetDirection(dir.x, dir.y);
		}

		if (m_Ball->GetPosition().x + m_Ball->GetSize().x > m_WindowWidth / 2) {
			m_ScoreSystem->AddScore(1);
			m_Ball->SetPosition(0.0f, 0.0f);
			m_Ball->SetDirection(-2.0f, 5.0f);
		}
		else if (m_Ball->GetPosition().x - m_Ball->GetSize().x < - m_WindowWidth / 2) {
			m_ScoreSystem->AddScore(2);
			m_Ball->SetPosition(0.0f, 0.0f);
			m_Ball->SetDirection(-2.0f, 5.0f);
		}

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