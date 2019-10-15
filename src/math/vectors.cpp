#include "vectors.hpp"

#include <cmath>

#define THRESHOLD 0.00001f

////////////////////////////////////////////////////////////////////////// VEC2

math::vec2::vec2() :
    x(0.0f), y(0.0f) {}

math::vec2::vec2(const float k) :
    x(k), y(k) {}

math::vec2::vec2(const float x, const float y) :
    x(x), y(y) {}

math::vec2::vec2(const vec2& v) :
    x(v.x), y(v.y) {}

float* math::vec2::data() {
    float ret[2] = { x,y };
    return ret;
}

void math::vec2::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
}

const float math::vec2::quadrance() const {
    return x * x + y * y;
}

const float math::vec2::length() const {
    return sqrt(quadrance());
}

const math::vec2 math::vec2::normalized() const {
    return *this / (*this).length();
}

math::vec2& math::vec2::operator=(const vec2& v) {
    x = v.x;
    y = v.y;
    return *this;
}

const math::vec2 math::vec2::operator-() const {
    return vec2(-x, -y);
}

math::vec2& math::vec2::operator+=(const vec2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

math::vec2& math::vec2::operator-=(const vec2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

math::vec2& math::vec2::operator*=(const float k) {
    x *= k;
    y *= k;
    return *this;
}

const math::vec2 math::vec2::operator+(const vec2& v) const {
    return vec2(x + v.x, y + v.y);
}

const math::vec2 math::vec2::operator-(const vec2& v) const {
    return vec2(x - v.x, y - v.y);
}

const math::vec2 math::vec2::operator/(const float k) const {
    return vec2(x / k, y / k);
}

const math::vec2 math::vec2::operator*(const float k) const {
    return vec2(x * k, y * k);
}

const bool math::vec2::operator==(const vec2& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) && (std::fabs(y - v.y) < THRESHOLD);
}

const bool math::vec2::operator!=(const vec2& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) || (std::fabs(y - v.y) >= THRESHOLD);
}

const float math::dot(const vec2& v1, const vec2& v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

const math::vec2 math::operator*(const float k, const vec2& v) {
    return v * k;
}

std::ostream& math::operator<<(std::ostream& os, const vec2& v) {
    os << "vec2(" << v.x << ", " << v.y << ")";
    return os;
}

std::istream& math::operator>>(std::istream& is, vec2& v) {
    is >> v.x;
    is >> v.y;
    return is;
}

////////////////////////////////////////////////////////////////////////// VEC3

math::vec3::vec3() :
    x(0.0f), y(0.0f), z(0.0f) {}

math::vec3::vec3(const float k) :
    x(k), y(k), z(k) {}

math::vec3::vec3(const float x, const float y, const float z) :
    x(x), y(y), z(z) {}

math::vec3::vec3(const vec3& v) :
    x(v.x), y(v.y), z(v.z) {}

float* math::vec3::data() {
    float ret[3] = { x, y, z };
    return ret;
}

void math::vec3::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
    if(std::fabs(z) < THRESHOLD) z = 0.0f;
}

const float math::vec3::quadrance() const {
    return x * x + y * y + z * z;
}

const float math::vec3::length() const {
    return sqrt(quadrance());
}

const math::vec3 math::vec3::normalized() const {
    return *this / (*this).length();
}

math::vec3& math::vec3::operator=(const vec3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

const math::vec3 math::vec3::operator-() const {
    return vec3(-x, -y, -z);
}

math::vec3& math::vec3::operator+=(const vec3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

math::vec3& math::vec3::operator-=(const vec3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

math::vec3& math::vec3::operator*=(const float k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

const math::vec3 math::vec3::operator+(const vec3& v) const {
    return vec3(x + v.x, y + v.y, z + v.z);
}

const math::vec3 math::vec3::operator-(const vec3& v) const {
    return vec3(x - v.x, y - v.y, z - v.z);
}

const math::vec3 math::vec3::operator/(const float k) const {
    return vec3(x / k, y / k, z / k);
}

const math::vec3 math::vec3::operator*(const float k) const {
    return vec3(x * k, y * k, z * k);
}

const bool math::vec3::operator==(const vec3& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) && (std::fabs(y - v.y) < THRESHOLD) && (std::fabs(z - v.z) < THRESHOLD);
}

const bool math::vec3::operator!=(const vec3& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) || (std::fabs(y - v.y) >= THRESHOLD) || (std::fabs(z - v.z) >= THRESHOLD);
}

const float math::dot(const vec3& v1, const vec3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const math::vec3 math::cross(const vec3& v1, const vec3& v2) {
    return vec3((v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x));
}

const math::vec3 math::operator*(const float k, const vec3& v) {
    return v * k;
}

std::ostream& math::operator<<(std::ostream& os, const vec3& v) {
    os << "vec3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

std::istream& math::operator>>(std::istream& is, vec3& v) {
    is >> v.x;
    is >> v.y;
    is >> v.z;
    return is;
}

////////////////////////////////////////////////////////////////////////// VEC4

math::vec4::vec4() :
    x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

math::vec4::vec4(const float k) :
    x(k), y(k), z(k), w(1.0f) {}

math::vec4::vec4(const float x, const float y, const float z, const float w) :
    x(x), y(y), z(z), w(w) {}

math::vec4::vec4(const math::vec3& v) :
    x(v.x), y(v.y), z(v.z), w(1.0f) {}

math::vec4::vec4(const vec4& v) :
    x(v.x), y(v.y), z(v.z), w(v.w) {}

float* math::vec4::data() {
    float ret[4] = { x, y, z, w };
    return ret;
}

void math::vec4::clean() {
    if(std::fabs(x) < THRESHOLD) x = 0.0f;
    if(std::fabs(y) < THRESHOLD) y = 0.0f;
    if(std::fabs(z) < THRESHOLD) z = 0.0f;
}

const float math::vec4::quadrance() const {
    return x * x + y * y + z * z;
}

const float math::vec4::length() const {
    return sqrt(quadrance());
}

const math::vec4 math::vec4::normalized() const {
    return *this / (*this).length();
}

math::vec4& math::vec4::operator=(const vec4& v) {
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}

const math::vec4 math::vec4::operator-() const {
    return vec4(-x, -y, -z, w);
}

math::vec4& math::vec4::operator+=(const vec4& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

math::vec4& math::vec4::operator-=(const vec4& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

math::vec4& math::vec4::operator*=(const float k) {
    x *= k;
    y *= k;
    z *= k;
    return *this;
}

const math::vec4 math::vec4::operator+(const vec4& v) const {
    return vec4(x + v.x, y + v.y, z + v.z, w);
}

const math::vec4 math::vec4::operator-(const vec4& v) const {
    return vec4(x - v.x, y - v.y, z - v.z, w);
}

const math::vec4 math::vec4::operator/(const float k) const {
    return vec4(x / k, y / k, z / k, w);
}

const math::vec4 math::vec4::operator*(const float k) const {
    return vec4(x * k, y * k, z * k, w);
}

const bool math::vec4::operator==(const vec4& v) const {
    return (std::fabs(x - v.x) < THRESHOLD) && (std::fabs(y - v.y) < THRESHOLD) && (std::fabs(z - v.z) < THRESHOLD);
}

const bool math::vec4::operator!=(const vec4& v) const {
    return (std::fabs(x - v.x) >= THRESHOLD) || (std::fabs(y - v.y) >= THRESHOLD) || (std::fabs(z - v.z) >= THRESHOLD);
}

const float math::dot(const vec4& v1, const vec4& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

const math::vec4 math::cross(const vec4& v1, const vec4& v2) {
    return vec4((v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x), v1.w);
}

const math::vec4 math::operator*(const float k, const vec4& v) {
    return v * k;
}

std::ostream& math::operator<<(std::ostream& os, const vec4& v) {
    os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.z << ")";
    return os;
}

std::istream& math::operator>>(std::istream& is, vec4& v) {
    is >> v.x;
    is >> v.y;
    is >> v.z;
    is >> v.w;
    return is;
}

////////////////////////////////////////////////////////////////////////// END