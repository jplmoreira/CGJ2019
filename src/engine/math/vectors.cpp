#include "vectors.hpp"

#define THRESHOLD 0.00001f

////////////////////////////////////////////////////////////////////////// VEC2

engine::math::vec2::vec2() :
    x(0.0f), y(0.0f) {}

engine::math::vec2::vec2(const float k) :
    x(k), y(k) {}

engine::math::vec2::vec2(const float x, const float y) :
    x(x), y(y) {}

engine::math::vec2::vec2(const vec2& v) :
    x(v.x), y(v.y) {}

float* engine::math::vec2::data() {
    return new float[2]{ x,y };
}

void engine::math::vec2::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
}

const float engine::math::vec2::quadrance() const {
    return x * x + y * y;
}

const float engine::math::vec2::length() const {
    return std::sqrt(quadrance());
}

const engine::math::vec2 engine::math::vec2::normalized() const {
    return *this / (*this).length();
}

engine::math::vec2& engine::math::vec2::operator=(const vec2& v) {
    x = v.x;
    y = v.y;
    return *this;
}

const engine::math::vec2 engine::math::vec2::operator-() const {
    return vec2(-x, -y);
}

engine::math::vec2& engine::math::vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

engine::math::vec2& engine::math::vec2::operator-=(const vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

engine::math::vec2& engine::math::vec2::operator*=(const float k) {
    x *= k;
    y *= k;
    return *this;
}

const engine::math::vec2 engine::math::vec2::operator+(const vec2& v) const {
    return vec2(x + v.x, y + v.y);
}

const engine::math::vec2 engine::math::vec2::operator-(const vec2& v) const {
    return vec2(x - v.x, y - v.y);
}

const engine::math::vec2 engine::math::vec2::operator/(const float k) const {
    return vec2(x / k, y / k);
}

const engine::math::vec2 engine::math::vec2::operator*(const float k) const {
    return vec2(x * k, y * k);
}

const bool engine::math::vec2::operator==(const vec2& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) && (std::fabs(y - v.y) < THRESHOLD);
}

const bool engine::math::vec2::operator!=(const vec2& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) || (std::fabs(y - v.y) >= THRESHOLD);
}

const float engine::math::dot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

const engine::math::vec2 engine::math::operator*(const float k, const vec2& v) {
    return v * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec2& v) {
    os << "vec2(" << v.x << ", " << v.y << ")";
    return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec2& v) {
    is >> v.x;
    is >> v.y;
    return is;
}

////////////////////////////////////////////////////////////////////////// VEC3

engine::math::vec3::vec3() :
    x(0.0f), y(0.0f), z(0.0f) {}

engine::math::vec3::vec3(const float k) :
    x(k), y(k), z(k) {}

engine::math::vec3::vec3(const float x, const float y, const float z) :
    x(x), y(y), z(z) {}

engine::math::vec3::vec3(const vec3& v) :
    x(v.x), y(v.y), z(v.z) {}

float* engine::math::vec3::data() {
    return new float[3]{ x,y,z };
}

void engine::math::vec3::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
    if(std::fabs(z) < THRESHOLD) z = 0.0f;
}

const float engine::math::vec3::quadrance() const {
    return x * x + y * y + z * z;
}

const float engine::math::vec3::length() const {
    return std::sqrt(quadrance());
}

const engine::math::vec3 engine::math::vec3::normalized() const {
    return *this / (*this).length();
}

engine::math::vec3& engine::math::vec3::operator=(const vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

const engine::math::vec3 engine::math::vec3::operator-() const {
    return vec3(-x, -y, -z);
}

engine::math::vec3& engine::math::vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

engine::math::vec3& engine::math::vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

engine::math::vec3& engine::math::vec3::operator*=(const float k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

const engine::math::vec3 engine::math::vec3::operator+(const vec3& v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

const engine::math::vec3 engine::math::vec3::operator-(const vec3& v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}

const engine::math::vec3 engine::math::vec3::operator/(const float k) const {
    return vec3(x / k, y / k, z / k);
}

const engine::math::vec3 engine::math::vec3::operator*(const float k) const {
    return vec3(x * k, y * k, z * k);
}

const bool engine::math::vec3::operator==(const vec3& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) &&
        (std::fabs(y - v.y) < THRESHOLD) &&
        (std::fabs(z - v.z) < THRESHOLD);
}

const bool engine::math::vec3::operator!=(const vec3& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) ||
        (std::fabs(y - v.y) >= THRESHOLD) ||
        (std::fabs(z - v.z) >= THRESHOLD);
}

const float engine::math::dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const engine::math::vec3 engine::math::cross(const vec3& v1, const vec3& v2) {
    return vec3((v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x));
}

const engine::math::vec3 engine::math::operator*(const float k, const vec3& v) {
    return v * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec3& v) {
    os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec3& v) {
    is >> v.x;
    is >> v.y;
    is >> v.z;
    return is;
}

////////////////////////////////////////////////////////////////////////// VEC4

engine::math::vec4::vec4() :
    x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

engine::math::vec4::vec4(const float k) :
    x(k), y(k), z(k), w(1.0f) {}

engine::math::vec4::vec4(const float x, const float y, const float z, const float w) :
    x(x), y(y), z(z), w(w) {}

engine::math::vec4::vec4(const math::vec3& v, const float w) :
    x(v.x), y(v.y), z(v.z), w(w) {}

engine::math::vec4::vec4(const vec4& v) :
    x(v.x), y(v.y), z(v.z), w(v.w) {}

float* engine::math::vec4::data() {
    return new float[4]{ x,y,z,w };
}

void engine::math::vec4::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
    if(std::fabs(z) < THRESHOLD) z = 0.0f;
}

const float engine::math::vec4::quadrance() const {
    return x * x + y * y + z * z;
}

const float engine::math::vec4::length() const {
    return std::sqrt(quadrance());
}

const engine::math::vec4 engine::math::vec4::normalized() const {
    return *this / (*this).length();
}

engine::math::vec4& engine::math::vec4::operator=(const vec4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

const engine::math::vec4 engine::math::vec4::operator-() const {
    return vec4(-x, -y, -z, w);
}

engine::math::vec4& engine::math::vec4::operator+=(const vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

engine::math::vec4& engine::math::vec4::operator-=(const vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

engine::math::vec4& engine::math::vec4::operator*=(const float k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

const engine::math::vec4 engine::math::vec4::operator+(const vec4& v) const {
    return vec4(x + v.x, y + v.y, z + v.z, w);
}

const engine::math::vec4 engine::math::vec4::operator-(const vec4& v) const {
    return vec4(x - v.x, y - v.y, z - v.z, w);
}

const engine::math::vec4 engine::math::vec4::operator/(const float k) const {
    return vec4(x / k, y / k, z / k, w);
}

const engine::math::vec4 engine::math::vec4::operator*(const float k) const {
    return vec4(x * k, y * k, z * k, w);
}

const bool engine::math::vec4::operator==(const vec4& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) &&
        (std::fabs(y - v.y) < THRESHOLD) &&
        (std::fabs(z - v.z) < THRESHOLD);
}

const bool engine::math::vec4::operator!=(const vec4& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) ||
        (std::fabs(y - v.y) >= THRESHOLD) ||
        (std::fabs(z - v.z) >= THRESHOLD);
}

const float engine::math::dot(const vec4& v1, const vec4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const engine::math::vec4 engine::math::cross(const vec4& v1, const vec4& v2) {
    return vec4((v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x), v1.w);
}

const engine::math::vec4 engine::math::operator*(const float k, const vec4& v) {
    return v * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const vec4& v) {
    os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}

std::istream& engine::math::operator>>(std::istream& is, vec4& v) {
    is >> v.x;
    is >> v.y;
    is >> v.z;
    is >> v.w;
    return is;
}

////////////////////////////////////////////////////////////////////////// END