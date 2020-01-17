#pragma once

#include <memory>
#include <vector>

#include "../include.hpp"
#include "../texture.hpp"
#include "../shader.hpp"
#include "mesh.hpp"

namespace engine {
    namespace geometry {
        struct object {
            std::shared_ptr<mesh> m;
            std::shared_ptr <shader> shdr;
            std::vector<std::unique_ptr<object>> children;
            std::vector<std::shared_ptr<texture>> textures;

            math::vec4 color;
            math::vec3 position;
            math::mat4 transform;
            math::qtrn quaternion;

            object();
            ~object();

            void add_node(std::unique_ptr<object>& obj);
            void draw();
        };
    }
}