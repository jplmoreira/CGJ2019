#include "mat_fact.hpp"

#include <cmath>

const float pi = std::acosf(-1);

engine::math::mat4 engine::math::mat_fact::translate(float dx, float dy, float dz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

engine::math::mat4 engine::math::mat_fact::scale(float sx, float sy, float sz) {
    return mat4(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

engine::math::mat4 engine::math::mat_fact::rotate(float angle, vec3& axis) {
    float rad = angle * pi / 180.0f;
    mat3 aux = mat3::identity_mat();
    if(axis.x == 1.0f) {
        aux = mat3(1.0f, 0.0f, 0.0f, 0.0f, std::cosf(rad), std::sinf(rad), 0.0f, -std::sinf(rad), std::cosf(rad));
    } else if(axis.y == 1.0f) {
        aux = mat3(std::cosf(rad), 0.0f, -std::sinf(rad), 0.0f, 1.0f, 0.0f, std::sinf(rad), 0.0f, std::cosf(rad));
    } else if(axis.z == 1.0f) {
        aux = mat3(std::cosf(rad), std::sinf(rad), 0.0f, -std::sinf(rad), std::cosf(rad), 0.0f, 0.0f, 0.0f, 1.0f);
    }
    return mat4(aux);
}

engine::math::mat3 engine::math::mat_fact::dual_mat(const vec3& v) {
    return mat3(0.0f, v.z, -v.y, -v.z, 0.0f, v.x, v.y, -v.x, 0.0f);
}

engine::math::mat3 engine::math::mat_fact::rodr_rot(const float angle, const vec3& axis) {
    float rad = angle * pi / 180.0f;
    mat3 a = dual_mat(axis.normalized());
    return mat3::identity_mat() + std::sin(rad) * a + (1 - std::cos(rad)) * (a * a);
}