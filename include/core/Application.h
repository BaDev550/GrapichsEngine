#pragma once

#include "Window.h"
#include "Input.h"
#include <renderer/Renderer.h>

class Application
{
private:
    float deltaTime;
    float lastFrame;

    Renderer* DGL_Renderer;
public:
    Application(){ DGL_Renderer = new Renderer(); }
    ~Application(){ delete DGL_Renderer; }
    
    void Start();
    void Update();
    void ProcessInput();
};
