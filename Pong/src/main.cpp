#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

int main() {
    glm::vec2 vec(1, 2);
    spdlog::info("Hello, {}, {}", vec.x, vec.y);

    // GLFW initialization code
    if (!glfwInit())
        return -1;

    // GLFW window creation code
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Handle Glad initialization failure
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    // Now you can use OpenGL functions
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render here
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}