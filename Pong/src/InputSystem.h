#pragma once

#include "GLFW/glfw3.h"

class InputSystem {
public:
	void Init();
	void Update();
	void Close();

	void SetWindow(GLFWwindow* window) {
		m_Window = window;
	}

	bool KeyDown(int key) {
		return glfwGetKey(m_Window, key);
	}
private:
	GLFWwindow* m_Window;
};