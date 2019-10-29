#pragma once

#include "../include.hpp"

namespace engine {
    namespace geometry {
        struct object {
            unsigned int num_indexes = 0;
            GLuint vao = 0;
            math::mat4 transform;
        };
    }
}