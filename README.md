# RayEctype
A toy framework for the "Raytracing in One Weekend" book. Instead of rendering to a image file, the raytracing rendering process is done in another thread, while a GUI thread presents the render result with a ImGui interface.

The important part (where the raytracing code will be added is in src/main_program.cpp).

# Dependencies
- CMake
- gl3w (fetched by CMake, needs internet connection for building!)
- glfw (fetched by CMake)
- glm (fetched by CMake)
- Dear ImGui (fetched by CMake)

# Compiling
    mkdir build && cd build
    cmake ..
    make
    ./ectype
