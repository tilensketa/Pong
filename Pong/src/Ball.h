#pragma once

#include <glm/glm.hpp>

#include "Quad.h"
#include "AABB.h"

class Ball {
public:
	Ball(float width, float height, float x, float y);

	void Draw(Shader& shader, Camera& camera);
	void Move(float ts);

	void SetPosition(float x, float y);
	void SetDirection(float x, float y);

	const glm::vec2& GetPosition() { return m_Position; }
	const glm::vec2& GetDirection() { return m_Direction; }
	const AABB& GetAABB() { return m_AABB; }
private:
	AABB CreateAABB();
private:
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Direction;
	float m_Speed = 2.0f;
	Quad m_Quad;
	float m_Width, m_Height;
	AABB m_AABB;
};