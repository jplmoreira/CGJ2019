#pragma once

#include <GLFW/glfw3.h>

class i_gl_app {
    virtual void window_close_callback(GLFWwindow* win) = 0;
    virtual void window_size_callback(GLFWwindow* win, int winx, int winy) = 0;
    virtual void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) = 0;
    virtual void mouse_callback(GLFWwindow* win, double xpos, double ypos) = 0;
    virtual void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) = 0;
    virtual void scroll_callback(GLFWwindow* win, double xoffset, double yoffset) = 0;
    virtual void joystick_callback(int jid, int event) = 0;
};