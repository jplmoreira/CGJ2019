#pragma once

#include <memory>
#include <vector>

#include "../include.hpp"
#include "../shader.hpp"
#include "mesh.hpp"

namespace engine {
    namespace geometry {
        struct object : std::enable_shared_from_this<object> {
            std::shared_ptr<mesh> m = nullptr;
            std::shared_ptr <shader> shdr = nullptr;
            std::shared_ptr<object> parent = nullptr;
            std::vector<std::shared_ptr<object>> children;

            math::vec4 color;
            math::mat4 transform;
            math::qtrn quaternion;

            object();

            std::shared_ptr<object> create_node();
            void draw();
        };
    }
}