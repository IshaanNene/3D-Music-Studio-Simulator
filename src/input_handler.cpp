#include "input_handler.h"
#include <GLFW/glfw3.h>
#include <iostream>

// Constructor to initialize camera parameters
InputHandler::InputHandler() {
    cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    lastX = 800.0f / 2.0f;
    lastY = 600.0f / 2.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    fov = 45.0f;
}

// Function to handle keyboard input (W, A, S, D for movement, ESC to close window)
void InputHandler::processInput(GLFWwindow *window, float deltaTime) {
    float cameraSpeed = 2.5f * deltaTime; // Adjust speed based on frame time

    // Move the camera based on WASD keys
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    // Close window with ESC key
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Function to handle mouse input (for camera movement: look around)
void InputHandler::processMouseMovement(GLFWwindow* window, float& lastX, float& lastY, bool& firstMouse) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Constrain the pitch to prevent the camera from flipping
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // Update the camera front vector based on new yaw and pitch values
    updateCameraVectors();
}

// Function to handle mouse scroll (zoom in/out)
void InputHandler::processMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}

// Update the camera's front vector based on yaw and pitch
void InputHandler::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// Get the view matrix (for camera positioning)
glm::mat4 InputHandler::getViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

// Get the projection matrix (for camera perspective)
glm::mat4 InputHandler::getProjectionMatrix(float width, float height) {
    return glm::perspective(glm::radians(fov), width / height, 0.1f, 100.0f);
}

