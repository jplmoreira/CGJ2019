#include "quaternions.hpp"

#define THRESHOLD 0.00001f

engine::math::quaternion::quaternion() : 
    t(0.0f) {}

engine::math::quaternion::quaternion(const float t, const float x, const float y, const float z) :
    t(t), v(x, y, z) {}

engine::math::quaternion::quaternion(const float t, const vec3& v) : 
    t(t), v(v) {}

engine::math::quaternion::quaternion(const vec3& axis, const float angle) {
    float rad = angle * pi / 180.0f;
    this->t = std::cosf(rad / 2.0f);
    this->v = axis.normalized() * std::sinf(rad / 2.0f);
}

void engine::math::quaternion::clean() {
    v.clean();
    if(std::fabs(t) < THRESHOLD) t = 0.0f;
}

const float engine::math::quaternion::quadrance() const {
    return t * t + v.x * v.x + v.y * v.y + v.z * v.z;
}

const float engine::math::quaternion::length() const {
    return std::sqrt(quadrance());
}

const engine::math::quaternion engine::math::quaternion::normalized() const {
    return *this / (*this).length();
}

const engine::math::quaternion engine::math::quaternion::conjugate() const {
    return quaternion(t, -v);
}

const engine::math::quaternion engine::math::quaternion::inverse() const {
    return conjugate() / quadrance();
}

const engine::math::vec3 engine::math::quaternion::axis() const {
    return v / std::sqrt(1-t*t);
}

const float engine::math::quaternion::angle() const {
    float rad = 2.0f * std::acosf(t);
    return rad * 180.0f / pi;
}

engine::math::quaternion& engine::math::quaternion::operator=(const quaternion& q) {
    this->t = q.t;
    this->v = q.v;
    return *this;
}

const engine::math::quaternion engine::math::quaternion::operator+(const quaternion& q) const {
    return quaternion(t + q.t, v + q.v);
}

const engine::math::quaternion engine::math::quaternion::operator*(const quaternion& q) const {
    return quaternion(t*q.t - dot(v, q.v), q.v * t + v * q.t + cross(v, q.v));
}

const engine::math::quaternion engine::math::quaternion::operator*(const float k) const {
    return quaternion(t * k, v * k);
}

const engine::math::quaternion engine::math::quaternion::operator/(const float k) const {
    return quaternion(t/k, v/k);
}

const bool engine::math::quaternion::operator==(const quaternion& q) const {
    return v == q.v && (std::fabs(t - q.t) < THRESHOLD);
}

const bool engine::math::quaternion::operator!=(const quaternion& q) const {
    return v != q.v && (std::fabs(t - q.t) >= THRESHOLD);
}

std::ostream& engine::math::operator<<(std::ostream& os, const quaternion& q) {
    os << "q(" << q.t << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z << ")";
    return os;
}
