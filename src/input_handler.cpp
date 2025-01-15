#include <GLFW/glfw3.h>
#include <iostream>

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    // TODO: Add input handling for camera movement and object interaction
}
