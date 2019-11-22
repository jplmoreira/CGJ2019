#include <array>

#include "scene.hpp"

engine::scene::scene() : root_obj(std::make_unique<geometry::object>()) {}

engine::scene::~scene() {
    root_obj.reset();
}

void engine::scene::draw() {
    root_obj->draw();
    glUseProgram(0);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}
