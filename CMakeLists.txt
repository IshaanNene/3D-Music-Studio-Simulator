cmake_minimum_required(VERSION 3.10)
project(3D_Music_Studio)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add executable
add_executable(3D_Music_Studio
    src/main.cpp
    src/window.cpp
    src/renderer.cpp
    src/simulation.cpp
    src/input_handler.cpp
    src/utilities/shaders.cpp
    src/utilities/model_loader.cpp
    src/utilities/math_utils.cpp
)

# Link libraries
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(assimp REQUIRED)
target_link_libraries(3D_Music_Studio glfw OpenGL::GL assimp)
