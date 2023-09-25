#include "RenderSystem.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

void RenderSystem::Init() {

	spdlog::info("Initializing RenderSystem");

	// Initialize GLFW and Glad
	if (!glfwInit())
		spdlog::critical("GLFW failed to initialize!");
	m_Window = glfwCreateWindow(m_Width, m_Height, "PONG", nullptr, nullptr);
	if (!m_Window) {
		spdlog::critical("Failed to initialize GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent((GLFWwindow*)m_Window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		spdlog::critical("Failed to initialized glad");
		glfwDestroyWindow((GLFWwindow*)m_Window);
		glfwTerminate();
	}
	glViewport(0, 0, m_Width, m_Height);

	// Make shader program
	m_Shader = new Shader("Shaders/default.vert", "Shaders/default.frag");

	m_Camera = new Camera(m_Width, m_Height, glm::vec3(0.0f, 0.0f, -5.0f));
}

void RenderSystem::Render() {
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_Shader->Activate();

	m_Camera->Matrix(*m_Shader, "camMatrix");




	//glfwSwapBuffers(m_Window);
}

void RenderSystem::Close() {
	glfwWindowShouldClose(m_Window);
	m_Shader->Delete();
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}