#include <core/Application.h>
#include <iostream>

using namespace Input;

void Application::Start(){
    Window::setSize(800, 800);
    Window::setTitle("2D Grapichs Engine");
    Window::setMode(WINDOWED);
    Window::setResizable(true);
    Window::setVsync(true);
    if (!Window::init())
        std::cout << "ERROR::Window::init() failed " << __FILE__ << " at " << __LINE__ << std::endl; return;

    DGL_Renderer->init();
}

void Application::Update(){
    while (!Window::windowShouldClose()){
        Window::clearBuffers(0.5f, 0.5f, 0.5f);
        
        float currentFrame = Window::getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();
        DGL_Renderer->renderFrame();
        Window::swapBuffers();
    }
    DGL_Renderer->cleanup();
    Window::close();
}

void Application::ProcessInput(){
    if (isKeyPressed(GLFW_KEY_ESCAPE))
        Window::close();
}
