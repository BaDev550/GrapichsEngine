#pragma once

#include <glfw/glfw3.h>

namespace Input
{
    static bool isKeyPressed(int keycode) { return glfwGetKey(glfwGetCurrentContext(), keycode) == GLFW_PRESS; }
    static bool isKeyReleased(int keycode) { return glfwGetKey(glfwGetCurrentContext(), keycode) == GLFW_RELEASE; }
    static bool isMouseButtonPressed(int buttonCode) { return glfwGetMouseButton(glfwGetCurrentContext(), buttonCode) == GLFW_PRESS; }
    static bool isMouseButtonReleased(int buttonCode) { return glfwGetMouseButton(glfwGetCurrentContext(), buttonCode) == GLFW_RELEASE; }
};
