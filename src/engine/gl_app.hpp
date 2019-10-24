#pragma once
#include "scene.hpp"
#include "shader.hpp"
#include "i_gl_app.hpp"

namespace engine {
    class gl_app : public i_gl_app {

        static gl_app* instance;
        shader sh;
        scene sc;

        gl_app() {}

    public:
        static gl_app* get_instance() {
            if(!instance) instance = new gl_app();
            return instance;
        }

        virtual void window_close_callback(GLFWwindow* win) override;
        virtual void window_size_callback(GLFWwindow* win, int winx, int winy) override;
        virtual void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) override;
        virtual void mouse_callback(GLFWwindow* win, double xpos, double ypos) override;
        virtual void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) override;
        virtual void scroll_callback(GLFWwindow* win, double xoffset, double yoffset) override;
        virtual void joystick_callback(int jid, int event) override;
        virtual void setup() override;
        virtual void display() override;
    };
}