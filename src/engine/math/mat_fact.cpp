#include "mat_fact.hpp"

engine::math::mat4 engine::math::mat_fact::translate(float dx, float dy, float dz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

engine::math::mat4 engine::math::mat_fact::scale(float sx, float sy, float sz) {
    return mat4(sx, 0.0f, 0.0f, 0.0f, 0.0f, sy, 0.0f, 0.0f, 0.0f, 0.0f, sz, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

engine::math::mat4 engine::math::mat_fact::rotate(float angle, vec3& axis) {
    const float pi = std::acosf(-1);
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
    const float pi = std::acosf(-1);
    float rad = angle * pi / 180.0f;
    mat3 a = dual_mat(axis.normalized());
    return mat3::identity_mat() + std::sinf(rad) * a + (1 - std::cosf(rad)) * (a * a);
}

engine::math::mat3 engine::math::mat_fact::rot_qtrn(const qtrn& q) {
    float v1 = 1.0f - 2.0f * (q.v.y * q.v.y + q.v.z * q.v.z);
    float v2 = 2.0f * (q.v.x * q.v.y + q.t * q.v.z);
    float v3 = 2.0f * (q.v.x * q.v.z - q.t * q.v.y);
    float v4 = 2.0f * (q.v.x * q.v.y - q.t * q.v.z);
    float v5 = 1.0f - 2.0f * (q.v.x * q.v.x + q.v.z * q.v.z);
    float v6 = 2.0f * (q.v.y * q.v.z + q.t * q.v.x);
    float v7 = 2.0f * (q.v.x * q.v.z + q.t * q.v.y);
    float v8 = 2.0f * (q.v.y * q.v.z - q.t * q.v.x);
    float v9 = 1.0f - 2.0f * (q.v.x * q.v.x + q.v.y * q.v.y);

    return mat3(v1, v2, v3, v4, v5, v6, v7, v8, v9);
}

engine::math::mat4 engine::math::mat_fact::shadow(const vec3& l_pos, const vec3& p_point, const vec3& p_normal) {
    float d = dot(-p_point, p_normal);
    vec4 light(l_pos, 0.0f);
    vec4 plane(p_normal, d);
    float pl_dot = dot(plane, light);

    float v1 = pl_dot - light.x * plane.x;
    float v5 = -light.x * plane.y;
    float v9 = -light.x * plane.z;
    float v13 = -light.x * plane.w;

    float v2 = -light.y * plane.x;
    float v6 = pl_dot - light.y * plane.y;
    float v10 = -light.y * plane.z;
    float v14 = -light.y * plane.w;

    float v3 =  -light.z * plane.x;
    float v7 = -light.z * plane.y;
    float v11 = pl_dot - light.z * plane.z;
    float v15 = -light.z * plane.w;

    float v4 = -light.w * plane.x;
    float v8 = -light.w * plane.y;
    float v12 = -light.w * plane.z;
    float v16 = pl_dot - light.w * plane.w;
    return mat4(v1, v2, v3, v4,
        v5, v6, v7, v8,
        v9, v10, v11, v12,
        v13, v14, v15, v16);
}
