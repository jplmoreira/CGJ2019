#include "quaternions.hpp"

#define THRESHOLD 0.00001f

engine::math::qtrn::qtrn() : 
    t(0.0f) {}

engine::math::qtrn::qtrn(const float t, const float x, const float y, const float z) :
    t(t), v(x, y, z) {}

engine::math::qtrn::qtrn(const float t, const vec3& v) : 
    t(t), v(v) {}

engine::math::qtrn::qtrn(const vec3& axis, const float angle) {
    float rad = angle * pi / 180.0f;
    this->t = std::cosf(rad / 2.0f);
    this->v = axis.normalized() * std::sinf(rad / 2.0f);
}

void engine::math::qtrn::clean() {
    v.clean();
    if(std::fabs(t) < THRESHOLD) t = 0.0f;
}

const float engine::math::qtrn::quadrance() const {
    return t * t + v.x * v.x + v.y * v.y + v.z * v.z;
}

const float engine::math::qtrn::length() const {
    return std::sqrt(quadrance());
}

const engine::math::qtrn engine::math::qtrn::normalized() const {
    return *this / (*this).length();
}

const engine::math::qtrn engine::math::qtrn::conjugate() const {
    return qtrn(t, -v);
}

const engine::math::qtrn engine::math::qtrn::inverse() const {
    return conjugate() / quadrance();
}

const engine::math::vec3 engine::math::qtrn::axis() const {
    return v / std::sqrt(1-t*t);
}

const float engine::math::qtrn::angle() const {
    float rad = 2.0f * std::acosf(t);
    return rad * 180.0f / pi;
}

engine::math::qtrn& engine::math::qtrn::operator=(const qtrn& q) {
    this->t = q.t;
    this->v = q.v;
    return *this;
}

const engine::math::qtrn engine::math::qtrn::operator+(const qtrn& q) const {
    return qtrn(t + q.t, v + q.v);
}

const engine::math::qtrn engine::math::qtrn::operator*(const qtrn& q) const {
    return qtrn(t*q.t - dot(v, q.v), q.v * t + v * q.t + cross(v, q.v));
}

const engine::math::qtrn engine::math::qtrn::operator*(const float k) const {
    return qtrn(t * k, v * k);
}

const engine::math::qtrn engine::math::qtrn::operator/(const float k) const {
    return qtrn(t/k, v/k);
}

const bool engine::math::qtrn::operator==(const qtrn& q) const {
    return v == q.v && (std::fabs(t - q.t) < THRESHOLD);
}

const bool engine::math::qtrn::operator!=(const qtrn& q) const {
    return v != q.v && (std::fabs(t - q.t) >= THRESHOLD);
}

const engine::math::qtrn engine::math::lerp(const qtrn& q1, const qtrn& q2, const float k) {
    float cos_angle = q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z + q1.t * q2.t;
    float k1 = 1.0f - k;
    float k2 = (cos_angle > 0.0f) ? k : -k;
    qtrn q = q1 * k1 + q2 * k2;
    return q.normalized();
}

const engine::math::qtrn engine::math::slerp(const qtrn& q1, const qtrn& q2, const float k) {
    float angle = std::acosf(q1.v.x * q2.v.x + q1.v.y * q2.v.y + q1.v.z * q2.v.z + q1.t * q2.t);
    float k1 = std::sinf((1.0f - k) * angle) / std::sinf(angle);
    float k2 = std::sinf(k * angle) / std::sinf(angle);
    qtrn q = q1 * k1 + q2 * k2;
    return q.normalized();
}

std::ostream& engine::math::operator<<(std::ostream& os, const qtrn& q) {
    os << "q(" << q.t << ", " << q.v.x << ", " << q.v.y << ", " << q.v.z << ")";
    return os;
}
