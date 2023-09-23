#include "Player.h"

Player::Player(float width, float height, float x, float y)
	: m_Width(width), m_Height(height) {
	SetPosition(x, y);
	m_Quad = Quad(m_Width, m_Height, m_Position.x, m_Position.y);
	m_AABB = CreateAABB();
}

void Player::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}

void Player::Input(GLFWwindow* window, float ts) {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		m_Position += up * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		m_Position -= up * ts;
	}

	const float height = 1.5f;
	if (m_Position.y > height / 2)
		m_Position.y = height / 2;
	else if (m_Position.y < -height / 2)
		m_Position.y = -height / 2;

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