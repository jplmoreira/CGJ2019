#pragma once

#include <vector>

#include "objects/geometry.hpp"

namespace engine {
    class scene {
        std::vector<objects::object> objs;

    public:
        void prepare();
        void draw(unsigned int program_id, unsigned int transform_id);
        void destroy();
    };
}