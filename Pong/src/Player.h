#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Quad.h"
#include "AABB.h"

class Player {
public:
	Player(float width, float height, float x, float y);

	void Draw(Shader& shader, Camera& camera);
	void Input(GLFWwindow* window, float ts);

	void SetPosition(float x, float y);

	const AABB& GetAABB() { return m_AABB; }
	const glm::vec2& GetPosition() { return glm::vec2(m_Position.x, m_Position.y); }
private:
	AABB CreateAABB();
private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	float m_Speed = 2.0f;
	Quad m_Quad;
	float m_Width, m_Height;
	AABB m_AABB;
};