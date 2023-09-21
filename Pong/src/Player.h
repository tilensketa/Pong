#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Quad.h"

class Player {
public:
	Player(float width, float height);

	void Draw(Shader& shader, Camera& camera);
	void Input(GLFWwindow* window, float ts);

private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	float m_Speed = 1.0f;
	Quad m_Quad;
	float m_Width, m_Height;
};