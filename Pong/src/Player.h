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

	void SetPosition(const glm::vec2& position);

	const AABB& GetAABB() { return m_AABB; }
	const glm::vec2& GetPosition() { return m_Position; }
private:
	AABB CreateAABB();
private:
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Size;
	float m_Speed = 300.0f;
	Quad m_Quad;
	AABB m_AABB;

	int m_Player;
};