#include <core/Window.h>
#include <iostream>

WindowStructer Window::window;

void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

Window::Window(unsigned int width, unsigned int height, const char* title){
    window.width = width;
    window.height = height;
    window.title = title; 
}

bool Window::init(){
    if (!glfwInit()){
        std::cout << "ERROR::GLFW::INIT" << __FILE__ << " at: " << __LINE__ << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
    glfwWindowHint(GLFW_RESIZABLE, window.bCanResize);
#endif
    
    GLFWmonitor* monitor = NULL;
    
    switch (window.VideoMode){
    case FULLSCREEN:
        monitor = glfwGetPrimaryMonitor();
        if (!monitor){ std::cout << "ERROR::GLFW::MONITOR" << __FILE__ << " at: " << __LINE__ << std::endl; }
        break;
    case WINDOWED:
        monitor = NULL;
        break;
    case WINDOWED_FULLSCREEN:
        std::cout << "On development" << std::endl;
        break;
    default:
        std::cout << "ERROR::WINDOW::VIDEO_MODE: No video mode selected making the default WINDOWED " << __FILE__ << " at: " << __LINE__ << std::endl;
        window.VideoMode = WINDOWED;
        break;
    }
    
    window.Window = glfwCreateWindow(window.width, window.height, window.title.c_str(), monitor, NULL);
    if (window.Window == NULL){
        std::cout << "ERROR::GLFW::WINDOW " << __FILE__ << " at: " << __LINE__ << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window.Window);
    glfwSwapInterval(window.bVsync);
    glfwSetFramebufferSizeCallback(window.Window, frameBufferSizeCallback);
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "ERROR::GLAD::INIT " << __FILE__ << " at: " << __LINE__ << std::endl;
        glfwTerminate();
        return false;
    }
    glViewport(0, 0, window.width, window.height);
    return true;
}

void Window::swapBuffers(){
    glfwGetFramebufferSize(window.Window, &window.fb_width, &window.fb_height);
    glfwPollEvents();
    glfwSwapBuffers(window.Window);
}

void Window::clearBuffers(const float red, const float green, const float blue){
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(red, green, blue, 1.0f);
}

void Window::close(){
    if (glfwWindowShouldClose(window.Window)){
        glfwSetWindowShouldClose(window.Window, true);
        glfwDestroyWindow(window.Window);
        glfwTerminate();
    }else{
        glfwSetWindowShouldClose(window.Window, true);
    }
}

void frameBufferSizeCallback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}
