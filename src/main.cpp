#include "engine/gl_engine.hpp"
#include "test/test.hpp"

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
    int gl_major = 4, gl_minor = 3;
    int is_fullscreen = 0;
    int is_vsync = 2;
    engine::gl_engine *engine = engine::gl_engine::get_instance();
    GLFWwindow* win = engine->setup(gl_major, gl_minor,
        640, 640, "OpenGL Viewer (GLFW)", is_fullscreen, is_vsync);
    engine->run(win);
    exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END