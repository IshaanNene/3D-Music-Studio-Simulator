#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    GLFWwindow* window;
    int width, height;
    const char* title;

    // Constructor
    Window(int w, int h, const char* t)
        : width(w), height(h), title(t), window(nullptr) {}

    // Initialize the window
    bool init() {
        // Initialize GLFW
        if (!glfwInit()) {
            std::cerr << "GLFW initialization failed!" << std::endl;
            return false;
        }

        // Set GLFW window hints (optional)
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create the GLFW window
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window) {
            std::cerr << "Failed to create GLFW window!" << std::endl;
            glfwTerminate();
            return false;
        }

        // Make the OpenGL context current
        glfwMakeContextCurrent(window);

        // Set GLFW callbacks
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Enable vsync
        glfwSwapInterval(1);

        return true;
    }

    // Handle window resizing
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    // Main loop
    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            // Poll events
            glfwPollEvents();

            // Render
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Swap buffers
            glfwSwapBuffers(window);
        }
    }

    // Clean up
    void cleanUp() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

// Main entry point
int main() {
    Window window(800, 600, "3D Music Studio Simulator");

    if (!window.init()) {
        return -1;  // Initialization failed
    }

    window.mainLoop();
    window.cleanUp();

    return 0;
}
