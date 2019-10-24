#pragma once

#include "gl_app.hpp"
#include <sstream>
#include <iostream>
#include <iomanip>

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