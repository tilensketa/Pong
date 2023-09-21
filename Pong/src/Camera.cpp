#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Camera::Camera(int width, int height, glm::vec3 position)
	: m_Width(width), m_Height(height), m_Position(position) {
	m_AspectRatio = (float)m_Width / m_Height;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 proj = glm::mat4(1.0f);

	proj = glm::ortho(-m_AspectRatio, m_AspectRatio, -1.0f, 1.0f, 0.1f, 100.0f);
	view = glm::translate(model, m_Position);

	int location = glGetUniformLocation(shader.ID, uniform);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(proj * view));
}

void Camera::Inputs(GLFWwindow* window, float ts) {
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_W)) {
		m_Position -= up * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_S)) {
		m_Position += up * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_D)) {
		m_Position -= right * ts;
	}
	if (glfwGetKey(window, GLFW_KEY_A)) {
		m_Position += right * ts;
	}
}