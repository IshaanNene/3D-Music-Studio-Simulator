#ifndef RENDERER_H
#define RENDERER_H

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <string>

class Renderer {
public:
    GLFWwindow* window;

    // Constructor
    Renderer();

    // Initialize GLFW and OpenGL
    void init();

    // Function to render a model
    void renderModel(const glm::vec3& position, const std::string& modelName);

    // Main rendering loop
    void renderLoop();
};

#endif // RENDERER_H
