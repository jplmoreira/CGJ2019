#pragma once

#include "vertex_attr.hpp"

#include "include.hpp"

namespace engine {
    struct shader {
        unsigned int program_id, transform_id;

        void setup();
        void destroy();
    };
}