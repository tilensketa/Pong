#include "Player.h"

Player::Player(glm::vec2 position, glm::vec2 size, int player)
	: m_Position(position), m_Size(size), m_Player(player) {
	m_Quad = Quad(m_Position, m_Size);
	m_AABB = CreateAABB();
}

void Player::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}

void Player::Input(float height, InputSystem input, float ts) {
	glm::vec2 up = glm::vec2(0.0f, 1.0f);
	int upKey = GLFW_KEY_UP;
	int downKey = GLFW_KEY_DOWN;
	switch (m_Player)
	{
		case 1:
			upKey = GLFW_KEY_W;
			downKey = GLFW_KEY_S;
			break;
		case 2:
			upKey = GLFW_KEY_UP;
			downKey = GLFW_KEY_DOWN;
			break;
	}
	if (input.KeyDown(upKey)) {
		m_Position += up * m_Speed * ts;
	}
	if (input.KeyDown(downKey)) {
		m_Position -= up * m_Speed * ts;
	}

	if (m_Position.y + m_Size.y / 2 > height / 2)
		m_Position.y = height / 2 - m_Size.y / 2;
	else if (m_Position.y - m_Size.y / 2 < -height / 2)
		m_Position.y = -height / 2 + m_Size.y / 2;

	m_Quad.SetPosition(m_Position);
	m_AABB = CreateAABB();
}

void Player::SetPosition(const glm::vec2& position) {
	m_Position = position;
	m_Quad.SetPosition(position);
}

AABB Player::CreateAABB() {
	glm::vec2 min = glm::vec2(m_Position.x - m_Size.x / 2, m_Position.y - m_Size.y / 2);
	glm::vec2 max = glm::vec2(m_Position.x + m_Size.x / 2, m_Position.y + m_Size.y / 2);
	return AABB(min, max);
}