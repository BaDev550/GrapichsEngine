#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Shader.h"
#include "Grid.h"

class Renderer
{
private:
    Shader core_shader;
    Grid grid_drawer;
public:
    Renderer() {}

    void init();
    void renderFrame();
    void cleanup();
};
