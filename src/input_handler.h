#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class InputHandler {
public:
    // Camera parameters
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;

    float yaw;
    float pitch;
    float fov;
    float lastX, lastY;

    // Constructor to initialize camera parameters
    InputHandler();

    // Method to process keyboard input (W, A, S, D for movement)
    void processInput(GLFWwindow* window, float deltaTime);

    // Method to process mouse movement for rotating the camera
    void processMouseMovement(GLFWwindow* window, float& lastX, float& lastY, bool& firstMouse);

    // Method to process mouse scroll for zooming in/out
    void processMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

    // Method to update the camera vectors based on yaw and pitch
    void updateCameraVectors();

    // Method to get the view matrix (camera positioning)
    glm::mat4 getViewMatrix();

    // Method to get the projection matrix (camera perspective)
    glm::mat4 getProjectionMatrix(float width, float height);
};

#endif // INPUT_HANDLER_H
