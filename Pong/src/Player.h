#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Quad.h"
#include "AABB.h"
#include "InputSystem.h"

class Player {
public:
	Player(glm::vec2 position, glm::vec2 size, int player);

	void Draw(Shader& shader, Camera& camera);
	void Input(float height, InputSystem input, float ts);

	void SetPosition(float x, float y);

	const AABB& GetAABB() { return m_AABB; }
	const glm::vec2& GetPosition() { return glm::vec2(m_Position.x, m_Position.y); }
private:
	AABB CreateAABB();
private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	float m_Speed = 300.0f;
	Quad m_Quad;
	float m_Width, m_Height;
	AABB m_AABB;

	int m_Player;
};