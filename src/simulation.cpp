#include <iostream>
#include <vector>
#include <cmath>

void simulateAcoustics() {
    std::cout << "Simulating acoustics..." << std::endl;

    // Parameters for simulation
    const double speed_of_sound = 343.0;  // m/s
    const double frequency = 440.0;       // Hz 
    const double amplitude = 1.0;         // Pascal
    const double duration = 1.0;          // seconds
    const double dt = 0.001;              // time step
    const double dx = 0.01;               // spatial step (m)

    // Create vectors to store pressure and velocity fields
    std::vector<double> pressure;
    std::vector<double> velocity;
    std::vector<double> pressure_prev;

    // Initialize simulation space
    const int grid_size = 100;
    pressure.resize(grid_size, 0.0);
    velocity.resize(grid_size, 0.0);
    pressure_prev.resize(grid_size, 0.0);

    // Initial conditions - Gaussian pulse
    const double pulse_width = 10.0;
    const double pulse_center = grid_size / 4;
    for (int i = 0; i < grid_size; i++) {
        pressure[i] = amplitude * exp(-pow((i - pulse_center) / pulse_width, 2));
        pressure_prev[i] = pressure[i];
    }

    // Constants for wave equation
    const double c = speed_of_sound;
    const double r = (c * dt / dx);
    const double r2 = r * r;

    // Main simulation loop - using FDTD (Finite Difference Time Domain) method
    for (double t = 0; t < duration; t += dt) {
        // Update velocity field (staggered leapfrog scheme)
        for (int i = 0; i < grid_size - 1; i++) {
            velocity[i] -= (dt / (dx * 1.2)) * (pressure[i + 1] - pressure[i]); // 1.2 is air density
        }

        // Store current pressure for update
        std::vector<double> pressure_next = pressure;

        // Update pressure field using wave equation
        for (int i = 1; i < grid_size - 1; i++) {
            pressure_next[i] = 2.0 * pressure[i] - pressure_prev[i] + 
                             r2 * (pressure[i + 1] - 2.0 * pressure[i] + pressure[i - 1]);
        }

        // Apply absorbing boundary conditions
        pressure_next[0] = pressure[1];
        pressure_next[grid_size - 1] = pressure[grid_size - 2];

        // Update pressure arrays for next iteration
        pressure_prev = pressure;
        pressure = pressure_next;

        // Ray tracing implementation
        if (static_cast<int>(t / dt) % 100 == 0) {  // Trace rays every 100 steps
            for (int ray = 0; ray < 10; ray++) {  // Launch 10 rays
                double ray_x = 0.0;
                double ray_y = ray * grid_size / 10.0;
                double ray_angle = M_PI / 4.0;  // 45 degrees
                
                // Trace ray path
                for (int step = 0; step < 50; step++) {
                    ray_x += cos(ray_angle) * dx;
                    ray_y += sin(ray_angle) * dx;
                    
                    // Check for boundary reflections
                    if (ray_y < 0 || ray_y >= grid_size) {
                        ray_angle = -ray_angle;  // Reflect
                    }
                }
            }
        }
    }

    std::cout << "Acoustic simulation completed." << std::endl;
}
