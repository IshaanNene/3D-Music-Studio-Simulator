#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include necessary headers for OpenGL, shaders, and model loading
#include "renderer.cpp"
#include "model_loader.cpp"

class Simulation {
public:
    std::vector<glm::vec3> instruments_positions; // Stores positions of instruments
    std::vector<std::string> instruments_names;   // Stores names of instruments

    // Initialize the simulation
    void init() {
        // For now, just initializing a few positions for the instruments
        instruments_positions.push_back(glm::vec3(0.0f, 0.0f, -5.0f));  // Example: Piano at the center
        instruments_names.push_back("Piano");

        instruments_positions.push_back(glm::vec3(3.0f, 0.0f, -5.0f));  // Example: Drum Kit to the right
        instruments_names.push_back("Drum Kit");

        instruments_positions.push_back(glm::vec3(-3.0f, 0.0f, -5.0f)); // Example: Guitar to the left
        instruments_names.push_back("Guitar");

        std::cout << "Simulation Initialized. Instruments placed in the 3D space." << std::endl;
    }

    // Update the positions of instruments (for interaction or user manipulation)
    void updateInstrumentPosition(const std::string& instrument_name, const glm::vec3& new_position) {
        for (size_t i = 0; i < instruments_names.size(); ++i) {
            if (instruments_names[i] == instrument_name) {
                instruments_positions[i] = new_position;
                std::cout << instrument_name << " moved to: " << new_position.x << ", " << new_position.y << ", " << new_position.z << std::endl;
                return;
            }
        }
        std::cout << "Instrument " << instrument_name << " not found!" << std::endl;
    }

    // Render the simulation scene (calls the renderer to display instruments)
    void renderSimulation(Renderer& renderer) {
        // Iterate over all instruments and render them at their respective positions
        for (size_t i = 0; i < instruments_positions.size(); ++i) {
            renderer.renderModel(instruments_positions[i], instruments_names[i]);
        }
    }

    // Simulation logic (e.g., interactions, movements, animations, etc.)
    void run(Renderer& renderer) {
        init(); // Initialize instruments

        // Main simulation loop (example loop for updating and rendering)
        while (true) {
            // Update positions, interactions, animations
            // For now, let's just render the scene
            renderSimulation(renderer);

            // You can add logic for updating instruments here
            // For example, if the user moves a piano:
            // updateInstrumentPosition("Piano", glm::vec3(1.0f, 0.0f, -5.0f));

            // This is a placeholder for breaking the loop, you may add an exit condition
            break; // Exiting immediately for the example (add real conditions here)
        }
    }
};

int main() {
    // Create a Renderer object (assume renderer has methods for setting up OpenGL and rendering models)
    Renderer renderer;

    // Create a Simulation object
    Simulation simulation;

    // Run the simulation
    simulation.run(renderer);

    return 0;
}
