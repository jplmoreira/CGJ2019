#pragma once

#include "../math/vectors.hpp"
#include "../math/matrices.hpp"

namespace engine {
    namespace objects {
        struct object {
            unsigned int num_indexes;
            unsigned int vao;
            math::mat4 trasform;
            math::vec4 color;
        };
    }
}