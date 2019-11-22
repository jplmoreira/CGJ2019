#pragma once

#include <vector>
#include <memory>

#include "geometry/object.hpp"

namespace engine {
    class scene {
        static std::shared_ptr<scene> instance;
        std::vector<std::shared_ptr<geometry::object>> objs;

    public:
        static std::shared_ptr<scene> get_instance() {
            if(!instance) instance = std::make_shared<scene>();
            return instance;
        }

        void create_objects();
        void draw();
    };
}