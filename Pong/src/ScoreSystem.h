#pragma once

class ScoreSystem {
public:
	void Init();
	void AddScore(int player);
	void Close();
private:
	int m_PlayerScore1;
	int m_PlayerScore2;
};