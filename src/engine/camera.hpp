#pragma once

#include <memory>

#include "include.hpp"

namespace engine {
    class camera {
        static std::shared_ptr<camera> instance;

        math::vec3 eye;
        math::vec3 center;
        math::vec3 up;
        math::mat4 project_mat;

    public:
        static std::shared_ptr<camera> get_instance() {
            if(!instance) instance = std::make_shared<camera>();
            return instance;
        }

        void look_at(const math::vec3 &eye, const math::vec3 &center,
            const math::vec3 &up);
        void perspective(const float fov, const float aspect,
            const float near, const float far);
        void orthographic(const float left, const float right,
            const float up, const float bottom, const float near, const float far);
        const math::mat4 view() const;
        const math::mat4 projection() const;
    };
}