#include <renderer/Renderer.h>

void Renderer::init(){
    core_shader.setupShader("shaders/core_vertex_shader.glsl", "shaders/core_fragment_shader.glsl");
    grid_drawer.createBufferObjects();
}

void Renderer::renderFrame(){
    core_shader.Use();
    grid_drawer.drawGrid();
}

void Renderer::cleanup(){
    
}
