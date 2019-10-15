#include "mat_fact.hpp"

math::mat4 math::mat_fact::translate(float dx, float dy, float dz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

math::mat4 math::mat_fact::scale(float sx, float sy, float sz) {
    return mat4(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}
