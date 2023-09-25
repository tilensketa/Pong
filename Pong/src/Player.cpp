#include "Player.h"

Player::Player(glm::vec2 position, glm::vec2 size, int player)
	: m_Width(size.x), m_Height(size.y), m_Position(glm::vec3(position, 0.0f)), m_Player(player) {
	m_Quad = Quad(m_Position, glm::vec2(m_Width, m_Height));
	m_AABB = CreateAABB();
}

void Player::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}

void Player::Input(float height, InputSystem input, float ts) {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
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

	if (m_Position.y + m_Height / 2 > height / 2)
		m_Position.y = height / 2 - m_Height / 2;
	else if (m_Position.y - m_Height / 2 < -height / 2)
		m_Position.y = -height / 2 + m_Height / 2;

	m_Quad.SetPosition(m_Position);
	m_AABB = CreateAABB();
}

void Player::SetPosition(float x, float y) {
	m_Position = glm::vec3(x, y, 0);
}

AABB Player::CreateAABB() {
	glm::vec2 min = glm::vec2(m_Position.x - m_Width / 2, m_Position.y - m_Height / 2);
	glm::vec2 max = glm::vec2(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2);
	return AABB(min, max);
}