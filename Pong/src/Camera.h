#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Shader.h"

class Camera {
public:
	Camera(int width, int height, glm::vec3 position);

	void Matrix(Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window, float ts);

	glm::vec3 m_Position;

	int m_Width;
	int m_Height;
	float m_AspectRatio;

	float m_Speed = 0.5f;
};