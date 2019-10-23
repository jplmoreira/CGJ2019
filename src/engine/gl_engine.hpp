#pragma once

#include <sstream>
#include <iostream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
namespace engine {
    class gl_engine {

        static gl_engine* instance;

        gl_engine() {}

    public:
        static gl_engine* get_instance() {
            if(!instance) instance = new gl_engine();
            return instance;
        }

        GLFWwindow* setup(int major, int minor,
            int winx, int winy, const char* title, int is_fullscreen, int is_vsync);

        void run(GLFWwindow* win);
    };
}