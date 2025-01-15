#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include custom headers for the renderer and model loader
#include "renderer.cpp"
#include "model_loader.cpp"

// Function to initialize the application
void initializeApp(Renderer &renderer) {
    std::cout << "Initializing the 3D Music Studio Simulator..." << std::endl;

    // Set up the initial state of the room or simulation environment
    // You can set up your initial positions or models here.
    std::cout << "Loading default room layout..." << std::endl;
    // You can load your default room JSON configuration (room layout, instruments positions, etc.)
    // For example: loadLayout("data/default_room.json");
}

// Function to process input (keyboard, mouse, etc.)
void processInput(GLFWwindow *window, float &cameraSpeed) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        // Example camera movement: Move forward
        cameraSpeed += 0.01f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        // Example camera movement: Move backward
        cameraSpeed -= 0.01f;
    }
}

// Main function
int main() {
    // Initialize the GLFW window and OpenGL context
    Renderer renderer;
    initializeApp(renderer);

    // Set up the camera movement speed or other parameters
    float cameraSpeed = 0.0f;

    // Main loop to render the 3D scene
    while (!glfwWindowShouldClose(renderer.window)) {
        // Process user input
        processInput(renderer.window, cameraSpeed);

        // Clear the screen before rendering the new frame
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render models or objects in the 3D space
        // Example: Render a model at a specific position
        renderer.renderModel(glm::vec3(0.0f, 0.0f, -5.0f), "Piano");

        // Render the next frame and swap buffers
        renderer.renderLoop();

        // Swap buffers (to display the rendered frame on the screen)
        glfwSwapBuffers(renderer.window);
    }

    // Clean up and close the application
    std::cout << "Closing the 3D Music Studio Simulator..." << std::endl;

    // Close the window and terminate GLFW
    glfwDestroyWindow(renderer.window);
    glfwTerminate();

    return 0;
}
