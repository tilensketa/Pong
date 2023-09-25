#include "ScoreSystem.h"

#include <spdlog/spdlog.h>

void ScoreSystem::Init() {

	spdlog::info("Initializing ScoreSystem");

	m_PlayerScore1 = 0;
	m_PlayerScore2 = 0;
}

void ScoreSystem::AddScore(int player) {
	switch (player)
	{
		case 1:
			m_PlayerScore1++;
			break;
		case 2:
			m_PlayerScore2++;
			break;
	}
	spdlog::info("{} : {}", m_PlayerScore1, m_PlayerScore2);
}

void ScoreSystem::Close() {
	m_PlayerScore1 = 0;
	m_PlayerScore2 = 0;
}