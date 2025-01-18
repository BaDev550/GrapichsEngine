#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "Shader.h"
#include "GridDrawer.h"

class Renderer
{
private:
    Shader core_shader;
    GridDrawer grid_drawer;
public:
    Renderer() {}

    void init();
    void renderFrame();
    void cleanup();
};
