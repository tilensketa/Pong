#pragma once

#include "RenderSystem.h"
#include "InputSystem.h"
#include "ScoreSystem.h"
#include "Camera.h"
#include "Player.h"
#include "Ball.h"

class Game {
public:
	Game(int width, int height);

	void Init();
	void Run();
	void Close();

private:
	int m_WindowWidth, m_WindowHeight;

	RenderSystem* m_RenderSystem;
	InputSystem* m_InputSystem;
	ScoreSystem* m_ScoreSystem;

	Camera* m_Camera = nullptr;
	Player* m_Player1 = nullptr;
	Player* m_Player2 = nullptr;
	Ball* m_Ball = nullptr;
	Quad* m_Background = nullptr;

	bool m_IsRunning = true;
};