#pragma once

#include <vector>
#include <memory>

#include "geometry/object.hpp"

namespace engine {
    struct scene {
        std::unique_ptr<engine::geometry::object> root_obj;

        scene();
        ~scene();

        void draw();
    };
}