#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

#include "Texture.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Camera.h"

#include "Quad.h"
#include "Player.h"

int main() {

    uint32_t HEIGHT = 500;
    uint32_t WIDTH = 800;

#pragma region Initialize GLFW and glad
    // GLFW initialization
    if (!glfwInit())
        return -1;
    // GLFW window creation
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);
    if (!window) {
        spdlog::critical("Failed to initialize GLFW window");
        glfwTerminate();
        return -1;
    }
    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initialize Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        // Handle Glad initialization failure
        spdlog::critical("Failed to initialized glad");
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }
#pragma endregion

    glViewport(0, 0, WIDTH, HEIGHT);

    Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

    // Texture
    Texture background("Textures/background.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    Quad backgroundQuad(3.0f, 2.0f, background);
    Player player(0.1f, 0.5f);
    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, 0.0f, -5.0f));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_FILL / GL_LINE

    double prevTime = 0.0f;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Calculate deltaTime
        double currTime = glfwGetTime();
        double delta = currTime - prevTime;
        prevTime = currTime;

        // Handle closing window with escape key
        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(window, true);

        // Clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.Activate();

        camera.Inputs(window, (float)delta);
        camera.Matrix(shaderProgram, "camMatrix");

        backgroundQuad.Draw(shaderProgram, camera);

        player.Input(window, (float)delta);
        player.Draw(shaderProgram, camera);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    // Delete everything
    shaderProgram.Delete();
    //brick.Delete();

    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}