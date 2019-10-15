#pragma once

#include "matrices.hpp"

namespace math {
    struct mat_fact {
        static mat4 translate(float dx, float dy, float dz);
        static mat4 scale(float sx, float sy, float sz);
        static mat4 rotate(float angle, vec3& axis);
    };
}