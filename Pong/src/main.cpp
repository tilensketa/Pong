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


int main() {

    uint32_t HEIGHT = 640;
    uint32_t WIDTH = 640;

    // Vertices coordinates
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     0.0f, 1.0f,
         0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,     1.0f, 0.0f
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

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

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Texture
    Texture brick("Textures/brick_wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    brick.texUnit(shaderProgram, "tex0", 0);

    Camera camera(WIDTH, HEIGHT, glm::vec3(0.0f, -0.5f, -2.0f));

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

        camera.Inputs(window, delta);
        camera.Matrix(0.1f, 100.0f, shaderProgram, "camMatrix");

        brick.Bind();
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    // Delete everything
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    shaderProgram.Delete();
    brick.Delete();

    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();
    return 0;
}