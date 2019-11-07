#pragma once

#include <memory>

#include "include.hpp"

struct direction {

};

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
        math::vec3 dir;
        const float velocity = 5.0f;
        bool rotation = false;
        math::vec2 last_pos = math::vec2(-1.0f, -1.0f);

    public:
        static std::shared_ptr<camera> get_instance() {
            if(!instance) instance = std::make_shared<camera>();
            return instance;
        }
        static enum class DIR {
            RIGHT,
            LEFT,
            UP,
            DOWN,
            STOP
        };

        camera();

        void create_block();
        void calculate_camera(double time_elapsed);
        void destroy_block();

        void setup(const bool ortho, const int w, const int h, const float fov, const float near, const float far);
        void resize(const int w, const int h);
        void make_ortho(const bool ortho);
        void field_of_view(const float fov);
        void view_planes(const float near, const float far);
        void look_at(const math::vec3 &eye, const math::vec3 &center,
            const math::vec3 &up);
        void move(DIR direction);
        void activate_rotation(bool activate);
        void rotate(float x, float y);
        void perspective(const float fov, const float aspect,
            const float near, const float far);
        void orthographic(const float left, const float right,
            const float up, const float bottom, const float near, const float far);
        const math::mat4 view() const;
        const math::mat4 projection() const;
    };
}