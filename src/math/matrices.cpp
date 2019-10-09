#include "matrices.h"

#define THRESHOLD 0.00001f

math::mat2::mat2() :
    data{ 0.0f } {}

math::mat2::mat2(float k) :
    data{ k, 0.0f, 0.0f, k } {}

math::mat2::mat2(float v1, float v2, float v3, float v4) :
    data{ v1, v2, v3, v4 } {}

math::mat2::mat2(const mat2& m) :
    data{ m.data[0], m.data[1], m.data[2], m.data[3] } {}

void math::mat2::clean() {
    for(int i = 0; i < 4; i++) {
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
    }
}

const float math::mat2::determinant() const {
    return data[0] * data[3] + data[1] * data[2];
}

const math::mat2 math::mat2::transposed() const {
    return mat2(data[0], data[2], data[1], data[3]);
}

const math::mat2 math::mat2::inversed() const {
    float det = determinant();
    if(det > 0) return mat2(data[3]/det, -data[1]/det, -data[2]/det, data[0]/det);
    return mat2(*this);
}

math::mat2& math::mat2::operator=(const mat2& m) {
    data[0] = m.data[0];
    data[1] = m.data[1];
    data[2] = m.data[2];
    data[3] = m.data[3];

    return *this;
}

const math::mat2 math::mat2::operator-() const {
    return mat2(-data[0],-data[1],-data[2],-data[3]);
}

math::mat2& math::mat2::operator+=(const mat2& m) {
    data[0] += m.data[0];
    data[1] += m.data[1];
    data[2] += m.data[2];
    data[3] += m.data[3];

    return *this;
}

math::mat2& math::mat2::operator-=(const mat2& m) {
    data[0] -= m.data[0];
    data[1] -= m.data[1];
    data[2] -= m.data[2];
    data[3] -= m.data[3];

    return *this;
}

math::mat2& math::mat2::operator*=(const float k) {
    data[0] *= k;
    data[1] *= k;
    data[2] *= k;
    data[3] *= k;

    return *this;
}

const math::mat2 math::mat2::operator+(const mat2& m) const {
    return mat2(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3]);
}

const math::mat2 math::mat2::operator-(const mat2& m) const {
    return mat2(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3]);
}

const math::mat2 math::mat2::operator*(const mat2& m) const {
    return mat2(data[0] * m.data[0], data[1] * m.data[1], data[2] * m.data[2], data[3] * m.data[3]);
}

const math::vec2 math::mat2::operator*(const vec2& v) const {
    float x = data[0] * v.x + data[2] * v.y;
    float y = data[1] * v.x + data[3] * v.y;
    return vec2(x, y);
}

const math::mat2 math::mat2::operator*(const float k) const {
    return mat2(data[0] * k, data[1] * k, data[2] * k, data[3] * k);
}

const bool math::mat2::operator==(const mat2& m) const {
    for(int i = 0; i < 4; i++) {
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return false;
    }
    return true;
}

const bool math::mat2::operator!=(const mat2& m) const {
    for(int i = 0; i < 4; i++) {
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return true;
    }
    return false;
}

math::mat2 math::mat2::identity_mat() {
    return mat2(1.0f, 0.0f, 0.0f, 1.0f);
}

math::mat3 math::mat2::translate_mat(float dx, float dy) {
    return mat3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, 1.0f);
}

math::mat2 math::mat2::scale_mat(float sx, float sy) {
    return mat2(sx, 0.0f, 0.0f, sy);
}

math::mat2 math::mat2::rotate(float angle) {
    return mat2(std::cos(angle), std::sin(angle), -std::sin(angle), std::cos(angle));
}

const math::mat2 math::operator*(const float k, const mat2& m) {
    return mat2(m.data[0] * k, m.data[1] * k, m.data[2] * k, m.data[3] * k);
}

std::ostream& math::operator<<(std::ostream& os, const mat2& m) {
    os << "mat2[" << m.data[0] << ", " << m.data[2] << "]" << std::endl;
    os << "    [" << m.data[1] << ", " << m.data[3] << "]";
    return os;
}

const math::mat3 math::operator*(const float k, const mat3& m) {
    return mat3();
}

std::ostream& math::operator<<(std::ostream& os, const mat3& m) {
    // TODO: insert return statement here
}

const math::mat4 math::operator*(const float k, const mat4& m) {
    return mat4();
}

std::ostream& math::operator<<(std::ostream& os, const mat4& m) {
    // TODO: insert return statement here
}

math::mat3::mat3() {}

math::mat3::mat3(float k) {}

math::mat3::mat3(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9) {}

void math::mat3::clean() {}

const float math::mat3::determinant() const {
    return 0.0f;
}

const math::mat3 math::mat3::transposed() const {
    return mat3();
}

const math::mat3 math::mat3::inversed() const {
    return mat3();
}

math::mat3& math::mat3::operator=(const mat3& m) {
    // TODO: insert return statement here
}

const math::mat3 math::mat3::operator-() const {
    return mat3();
}

math::mat3& math::mat3::operator+=(const mat3& m) {
    // TODO: insert return statement here
}

math::mat3& math::mat3::operator-=(const mat3& m) {
    // TODO: insert return statement here
}

math::mat3& math::mat3::operator*=(const float k) {
    // TODO: insert return statement here
}

const math::mat3 math::mat3::operator+(const mat3& m) const {
    return mat3();
}

const math::mat3 math::mat3::operator-(const mat3& m) const {
    return mat3();
}

const math::mat3 math::mat3::operator*(const mat3& m) const {
    return mat3();
}

const math::vec3 math::mat3::operator*(const vec3& v) const {
    return vec3();
}

const math::mat3 math::mat3::operator*(const float k) const {
    return mat3();
}

const bool math::mat3::operator==(const mat3& m) const {
    return false;
}

const bool math::mat3::operator!=(const mat3& m) const {
    return false;
}

math::mat3 math::mat3::identity_mat() {
    return mat3();
}

math::mat4 math::mat3::translate_mat(float dx, float dy, float dz) {
    return mat4();
}

math::mat3 math::mat3::scale_mat(float sx, float sy, float sz) {
    return mat3();
}

math::mat3 math::mat3::rotate(float angle, vec3& axis) {
    return mat3();
}

math::mat4::mat4() {}

math::mat4::mat4(float k) {}

math::mat4::mat4(float v1, float v2, float v3, float v4, float v5, float v6, float v7, float v8, float v9, float v10, float v11, float v12, float v13, float v14, float v15, float v16) {}

void math::mat4::clean() {}

const float math::mat4::determinant() const {
    return 0.0f;
}

const math::mat4 math::mat4::transposed() const {
    return mat4();
}

const math::mat4 math::mat4::inversed() const {
    return mat4();
}

math::mat4& math::mat4::operator=(const mat4& m) {
    // TODO: insert return statement here
}

const math::mat4 math::mat4::operator-() const {
    return mat4();
}

math::mat4& math::mat4::operator+=(const mat4& m) {
    // TODO: insert return statement here
}

math::mat4& math::mat4::operator-=(const mat4& m) {
    // TODO: insert return statement here
}

math::mat4& math::mat4::operator*=(const float k) {
    // TODO: insert return statement here
}

const math::mat4 math::mat4::operator+(const mat4& m) const {
    return mat4();
}

const math::mat4 math::mat4::operator-(const mat4& m) const {
    return mat4();
}

const math::mat4 math::mat4::operator*(const mat4& m) const {
    return mat4();
}

const math::vec4 math::mat4::operator*(const vec4& v) const {
    return vec4();
}

const math::mat4 math::mat4::operator*(const float k) const {
    return mat4();
}

const bool math::mat4::operator==(const mat4& m) const {
    return false;
}

const bool math::mat4::operator!=(const mat4& m) const {
    return false;
}

math::mat4 math::mat4::identity_mat() {
    return mat4();
}

math::mat4 math::mat4::translate_mat(float dx, float dy, float dz) {
    return mat4();
}

math::mat4 math::mat4::scale_mat(float sx, float sy, float sz) {
    return mat4();
}

math::mat4 math::mat4::rotate(float angle, vec3& axis) {
    return mat4();
}
