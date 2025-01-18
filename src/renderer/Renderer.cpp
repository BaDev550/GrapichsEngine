#include <renderer/Renderer.h>

void Renderer::init(){
    core_shader.setupShader("shaders/core_shader.vert", "shaders/core_shader.frag");
    grid_drawer.createBufferObjects();
}

void Renderer::renderFrame(){
    core_shader.Use();
    grid_drawer.drawGrid();
}

void Renderer::cleanup(){

}
