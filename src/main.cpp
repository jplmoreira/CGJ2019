#include "gl_engine.hpp"
#include "test/test.hpp"

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
    /*int gl_major = 4, gl_minor = 3;
    int is_fullscreen = 0;
    int is_vsync = 2;
    gl_engine *engine = gl_engine::get_instance();
    GLFWwindow* win = engine->setup(gl_major, gl_minor,
        640, 480, "OpenGL Viewer (GLFW)", is_fullscreen, is_vsync);
    engine->run(win);*/
    mat_tests();
    while(true) {}
    exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END