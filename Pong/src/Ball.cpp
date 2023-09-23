#include "Ball.h"

#include <spdlog/spdlog.h>

Ball::Ball(float width, float height, float x, float y)
	: m_Width(width), m_Height(height) {
	SetPosition(x, y);
	Texture ballSprite = Texture("Textures/circle.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	m_Quad = Quad(m_Width, m_Height, m_Position.x, m_Position.y, ballSprite);
	m_Direction = glm::normalize(glm::vec2(2, 1));
	m_AABB = CreateAABB();
}

void Ball::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}
void Ball::Move(float ts) {
	m_Position += m_Speed * m_Direction * ts;

	const float width = 3.0f;
	const float height = 2.0f;
	if (m_Position.x > width / 2) {
		spdlog::info("Lost");
		m_Position = glm::vec2(0.0f, 0.0f);
		m_Direction = glm::normalize(glm::vec2(-2.0f, 5.0f));
	}
	else if (m_Position.x < -width / 2)
		m_Direction.x = -m_Direction.x;

	if (m_Position.y > height / 2)
		m_Direction.y = -m_Direction.y;
	else if (m_Position.y < -height / 2)
		m_Direction.y = -m_Direction.y;

	m_Quad.SetPosition(glm::vec3(m_Position.x, m_Position.y, 0));
	m_AABB = CreateAABB();
}

void Ball::SetPosition(float x, float y) {
	m_Position = glm::vec3(x, y, 0);
}

void Ball::SetDirection(float x, float y) {
	m_Direction = glm::vec2(x, y);
}

AABB Ball::CreateAABB() {
	glm::vec2 min = glm::vec2(m_Position.x - m_Width / 2, m_Position.y - m_Height / 2);
	glm::vec2 max = glm::vec2(m_Position.x + m_Width / 2, m_Position.y + m_Height / 2);
	return AABB(min, max);
}