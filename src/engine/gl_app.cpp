#include "gl_app.hpp"

#include <iostream>

engine::gl_app* engine::gl_app::instance;

void engine::gl_app::window_close_callback(GLFWwindow* win) {
    std::cout << "closing..." << std::endl;
    sh.destroy();
    sc.destroy();
}

void engine::gl_app::window_size_callback(GLFWwindow* win, int winx, int winy) {
    //std::cout << "size: " << winx << " " << winy << std::endl;
    glViewport(0, 0, winx, winy);
}

void engine::gl_app::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    //std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
    //if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    //    glfwSetWindowShouldClose(win, GLFW_TRUE);
    //    window_close_callback(win);
    //}
}

void engine::gl_app::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
    //std::cout << "mouse: " << xpos << " " << ypos << std::endl;
}

void engine::gl_app::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    //std::cout << "button: " << button << " " << action << " " << mods << std::endl;
}

void engine::gl_app::scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
    //std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
}

void engine::gl_app::joystick_callback(int jid, int event) {
    //std::cout << "joystick: " << jid << " " << event << std::endl;
}

void engine::gl_app::setup() {
    sh.setup();
    sc.prepare();
}

void engine::gl_app::display() {
    sc.draw(sh.program_id, sh.transform_id);
}