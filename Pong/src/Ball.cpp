#include "Ball.h"

#include <spdlog/spdlog.h>

Ball::Ball(const glm::vec2& position, const glm::vec2& size)
	: m_Position(position), m_Size(size) {
	Texture ballSprite = Texture("Textures/ball.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
	m_Quad = Quad(m_Position, m_Size, ballSprite);
	m_Direction = glm::normalize(glm::vec2(2, 1));
	m_AABB = CreateAABB();
}

void Ball::Draw(Shader& shader, Camera& camera) {
	m_Quad.Draw(shader, camera);
}

void Ball::Move(glm::vec2 border, float ts) {
	m_Position += m_Speed * m_Direction * ts;

	if (m_Position.x - m_Size.x / 2 < -border.x / 2)
		m_Direction.x = -m_Direction.x;

	if (m_Position.y + m_Size.y / 2 > border.y / 2)
		m_Direction.y = -m_Direction.y;
	else if (m_Position.y - m_Size.y / 2 < -border.y / 2)
		m_Direction.y = -m_Direction.y;

	m_Quad.SetPosition(m_Position);
	m_AABB = CreateAABB();
}

void Ball::SetPosition(const glm::vec2& position) {
	m_Position = position;
	m_Quad.SetPosition(position);
}

void Ball::SetDirection(const glm::vec2& direction) {
	m_Direction = glm::normalize(direction);
}

AABB Ball::CreateAABB() {
	glm::vec2 min = glm::vec2(m_Position.x - m_Size.x / 2, m_Position.y - m_Size.y / 2);
	glm::vec2 max = glm::vec2(m_Position.x + m_Size.x / 2, m_Position.y + m_Size.y / 2);
	return AABB(min, max);
}