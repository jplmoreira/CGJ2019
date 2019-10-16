#include "mat_fact.hpp"

#include <cmath>

const double pi = std::acos(-1);

math::mat4 math::mat_fact::translate(float dx, float dy, float dz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

math::mat4 math::mat_fact::scale(float sx, float sy, float sz) {
    return mat4(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

math::mat4 math::mat_fact::rotate(float angle, vec3& axis) {
    float rad = angle * pi / 180.0f;
    mat3 aux = mat3::identity_mat();
    if(axis.x == 1.0f) {
        aux = mat3(1.0f, 0.0f, 0.0f, 0.0f, std::cos(rad), -std::sin(rad), 0.0f, std::sin(rad), std::cos(rad));
    } else if(axis.y == 1.0f) {
        aux = mat3(std::cos(rad), 0.0f, std::sin(rad), 0.0f, 1.0f, 0.0f, -std::sin(rad), 0.0f, std::cos(rad));
    } else if(axis.z == 1.0f) {
        aux = mat3(std::cos(rad), -std::sin(rad), 0.0f, std::sin(rad), std::cos(rad), 0.0f, 0.0f, 0.0f, 1.0f);
    }
    return mat4(aux);
}
