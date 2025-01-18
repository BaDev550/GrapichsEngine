#pragma once

#include "Window.h"

class Application
{
private:
    float deltaTime;
    float lastFrame;
public:
    Application() = default;

    void Start();
    void Update();
};
