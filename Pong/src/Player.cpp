#include "Player.h"

Player::Player(float width, float height)
	: m_Width(width), m_Height(height) {
	m_Quad = Quad(m_Width, m_Height);
}

void Player::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}

void Player::Input(GLFWwindow* window, float ts) {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_UP)) {
		m_Position += up * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN)) {
		m_Position -= up * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		m_Position += right * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		m_Position -= right * ts;
	}
	m_Quad.Move(m_Position);
}