#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(int width, int height, glm::vec3 position)
	: m_Width(width), m_Height(height), m_Position(position) {
	m_AspectRatio = (float)m_Width / (float)m_Height;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	proj = glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
	float halfWidth = (float)m_Width / 2.0f;
	float halfHeight = (float)m_Height / 2.0f;
	proj = glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, 0.1f, 100.0f);
	view = glm::translate(model, m_Position);

	int location = glGetUniformLocation(shader.ID, uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(InputSystem input, float ts) {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	if (input.KeyDown(GLFW_KEY_W)) {
		m_Position -= up * ts;
	}
	if (input.KeyDown(GLFW_KEY_S)) {
		m_Position += up * ts;
	}
	if (input.KeyDown(GLFW_KEY_A)) {
		m_Position -= right * ts;
	}
	if (input.KeyDown(GLFW_KEY_S)) {
		m_Position += right * ts;
	}
}