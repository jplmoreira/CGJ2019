#pragma once

#include <memory>

#include "include.hpp"

namespace engine {
    class camera {
        static std::shared_ptr<camera> instance;

        bool ortho;
        math::vec3 eye;
        math::vec3 center;
        math::vec3 up;
        math::mat4 project_mat;
        GLuint ubo_id;
        float fov, near, far;

    public:
        static std::shared_ptr<camera> get_instance() {
            if(!instance) instance = std::make_shared<camera>();
            return instance;
        }

        void create_block();
        void calculate_camera();
        void destroy_block();

        void setup(const bool ortho, const int w, const int h, const float fov, const float near, const float far);
        void resize(const int w, const int h);
        void make_ortho(const bool ortho);
        void field_of_view(const float fov);
        void view_planes(const float near, const float far);
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