#pragma once

#include <glm/glm.hpp>

#include "Quad.h"
#include "AABB.h"

class Ball {
public:
	Ball(const glm::vec2& position, const glm::vec2& size);

	void Draw(Shader& shader, Camera& camera);
	void Move(glm::vec2 border, float ts);

	void SetPosition(const glm::vec2& position);
	void SetDirection(const glm::vec2& direction);

	const glm::vec2& GetPosition() { return m_Position; }
	const glm::vec2& GetDirection() { return m_Direction; }
	const glm::vec2& GetSize() { return m_Size; }
	const AABB& GetAABB() { return m_AABB; }
private:
	AABB CreateAABB();
private:
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Size;
	glm::vec2 m_Direction;
	float m_Speed = 400.0f;
	Quad m_Quad;
	AABB m_AABB;
};