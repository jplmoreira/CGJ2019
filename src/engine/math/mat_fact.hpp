#pragma once

#include "matrices.hpp"
#include "quaternions.hpp"

namespace engine {
    namespace math {
        struct mat_fact {
            static mat4 translate(float dx, float dy, float dz);
            static mat4 scale(float sx, float sy, float sz);
            static mat4 rotate(float angle, vec3& axis);
            static mat3 dual_mat(const vec3& v);
            static mat3 rodr_rot(const float angle, const vec3& axis);
            static mat3 rot_qtrn(const qtrn& q);
            static mat4 shadow(const vec3& l_pos, const vec3& p_point, const vec3& p_normal);
        };
    }
}