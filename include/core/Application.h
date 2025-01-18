#pragma once

#include "Window.h"
#include "Input.h"
#include <renderer/Renderer.h>

class Application
{
private:
    float deltaTime;
    float lastFrame;

    Renderer DGL_Renderer;
public:
    Application() {}
    
    void Start();
    void Update();
    void ProcessInput();

    Renderer GetRenderer() { return DGL_Renderer; }
};
