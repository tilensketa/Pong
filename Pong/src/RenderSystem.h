#pragma once

#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Camera.h"

class RenderSystem {
public:
	void Init();
	void Render();
	void Close();

	void SetWidth(int width) { m_Width = width; }
	void SetHeight(int height) { m_Height = height; }

	GLFWwindow* GetWindow() const { return m_Window; }
	Shader* GetShader() const { return m_Shader; }
	Camera* GetCamera() const { return m_Camera; }
private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;

	Shader* m_Shader;
	Camera* m_Camera;
};