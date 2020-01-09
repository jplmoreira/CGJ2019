#include <memory>

#include "engine/gl_engine.hpp"
#include "tangram.hpp"
#include "planar.hpp"
#include "bloom.hpp"

int main(int argc, char* argv[]) {
    int gl_major = 4, gl_minor = 3;
    int is_fullscreen = 0;
    int is_vsync = 1;
	engine::gl_engine::get_instance()->app = std::make_unique<bloom>();
    GLFWwindow* win = engine::gl_engine::get_instance()->setup(gl_major, gl_minor,
        1280, 1000, "CGJ Project", is_fullscreen, is_vsync);
	engine::gl_engine::get_instance()->run(win);
    exit(EXIT_SUCCESS);
}