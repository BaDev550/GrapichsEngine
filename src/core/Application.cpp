#include <core/Application.h>
#include <iostream>

void Application::Start(){
    Window::setSize(800, 800);
    Window::setTitle("3D Grapichs Engine");
    Window::setMode(WINDOWED);
    Window::setResizable(true);
    Window::setVsync(true);
    if (!Window::init())
        std::cout << "ERROR::Window::init() failed " << __FILE__ << " at " << __LINE__ << std::endl; return;
}

void Application::Update(){
    while (!Window::windowShouldClose()){
        float currentFrame = Window::getTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        Window::swapBuffers();
    }
    Window::close();
}
