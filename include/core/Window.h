#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <string>

enum WindowMode
{
    WINDOWED,
    FULLSCREEN,
    WINDOWED_FULLSCREEN,
};

struct WindowStructer
{
    unsigned int width = 800, height = 800;
    int fb_width, fb_height;
    std::string title = "Grapichs Engine";
    GLFWwindow* Window;
    WindowMode VideoMode = WINDOWED;

    // Window Configs
    bool bCanResize = true;
    bool bVsync = true;
};

class Window
{
private:
    static WindowStructer window;
public:
    Window(unsigned int width, unsigned int height, const char* title);

    static bool init();
    static void swapBuffers();
    static void close();
    
    static void setSize(unsigned int width, unsigned int height) { window.width = width, window.height = height; };
    __forceinline unsigned int getWidth() { return window.width; };
    __forceinline unsigned int getHeight() { return window.height; };
    
    static void setTitle(const char* title) { window.title = title; };
    __forceinline std::string getTitle() { return window.title; };
    
    static void setMode(WindowMode mode) { window.VideoMode = mode; }
    __forceinline static WindowMode getMode() { return window.VideoMode; }

    static void setVsync(bool vsync) { window.bVsync = vsync; }
    __forceinline static bool getVsync() { return window.bVsync; }

    static void setResizable(bool resizable) { window.bCanResize = resizable; }
    __forceinline static bool getResizable() { return window.bCanResize; }

    __forceinline static bool windowShouldClose() { return glfwWindowShouldClose(window.Window); }
    __forceinline static float getTime() { return glfwGetTime(); }
    
    __forceinline static int getFrameBufferWidth() { return window.fb_width; }
    __forceinline static int getFrameBufferHeight() { return window.fb_height; }
};
