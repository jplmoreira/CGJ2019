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
    if(det > 0) return mat2(data[3] / det, -data[1] / det, -data[2] / det, data[0] / det);
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
    return mat2(-data[0], -data[1], -data[2], -data[3]);
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
    return mat2(1.0f);
}

math::mat3 math::mat2::translate_mat(const float dx, const float dy) {
    return mat3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, 1.0f);
}

math::mat2 math::mat2::scale_mat(const float sx, const float sy) {
    return mat2(sx, 0.0f, 0.0f, sy);
}

math::mat2 math::mat2::rotate(const float angle) {
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

math::mat3::mat3() :
    data{ 0.0f } {}

math::mat3::mat3(float k) :
    data{ k, 0.0f, 0.0f,
    0.0f, k, 0.0f,
    0.0f, 0.0f, k } {}

math::mat3::mat3(float v1, float v2, float v3,
    float v4, float v5, float v6,
    float v7, float v8, float v9) : 
    data{v1,v2,v3,v4,v5,v6,v7,v8,v9} {}

void math::mat3::clean() {
    for(int i = 0; i < 9; i++) {
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
    }
}

const float math::mat3::determinant() const {
    return data[0] * minimat_det(0, *this) - data[3] * minimat_det(3, *this) + data[6] * minimat_det(6, *this);
}

const math::mat3 math::mat3::transposed() const {
    return mat3(data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8]);
}

const math::mat3 math::mat3::inversed() const {
    return mat3();
}

math::mat3& math::mat3::operator=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] = m.data[i];
    return *this;
}

const math::mat3 math::mat3::operator-() const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = -data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

math::mat3& math::mat3::operator+=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] += m.data[i];
    return *this;
}

math::mat3& math::mat3::operator-=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] -= m.data[i];
    return *this;
}

math::mat3& math::mat3::operator*=(const float k) {
    for(int i = 0; i < 9; i++) data[i] *= k;
    return *this;
}

const math::mat3 math::mat3::operator+(const mat3& m) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i]+m.data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const math::mat3 math::mat3::operator-(const mat3& m) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] + m.data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const math::mat3 math::mat3::operator*(const mat3& m) const {
    float res0 = data[0] * m.data[0] + data[3] * m.data[1] + data[6] * m.data[2];
    float res1 = data[1] * m.data[0] + data[4] * m.data[1] + data[7] * m.data[2];
    float res2 = data[2] * m.data[0] + data[5] * m.data[1] + data[8] * m.data[2];

    float res3 = data[0] * m.data[3] + data[3] * m.data[4] + data[6] * m.data[5];
    float res4 = data[1] * m.data[3] + data[4] * m.data[4] + data[7] * m.data[5];
    float res5 = data[2] * m.data[3] + data[5] * m.data[4] + data[8] * m.data[5];

    float res6 = data[0] * m.data[6] + data[3] * m.data[7] + data[6] * m.data[8];
    float res7 = data[1] * m.data[6] + data[4] * m.data[7] + data[7] * m.data[8];
    float res8 = data[2] * m.data[6] + data[5] * m.data[7] + data[8] * m.data[8];
    return mat3(res0, res1, res2, res3, res4, res5, res6, res7, res8);
}

const math::vec3 math::mat3::operator*(const vec3& v) const {
    float x = data[0] * v.x + data[3] * v.y + data[6] * v.z;
    float y = data[1] * v.x + data[4] * v.y + data[7] * v.z;
    float z = data[2] * v.x + data[5] * v.y + data[8] * v.z;

    return vec3(x, y, z);
}

const math::mat3 math::mat3::operator*(const float k) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] * k;
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const bool math::mat3::operator==(const mat3& m) const {
    for(int i = 0; i < 4; i++) {
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return false;
    }
    return true;
}

const bool math::mat3::operator!=(const mat3& m) const {
    for(int i = 0; i < 4; i++) {
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return true;
    }
    return false;
}

math::mat3 math::mat3::identity_mat() {
    return mat3(1.0f);
}

math::mat4 math::mat3::translate_mat(const float dx, const float dy, const float dz) {
    return mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, dx, dy, dz, 1.0f);
}

math::mat3 math::mat3::scale_mat(const float sx, const float sy, const float sz) {
    return mat3(sx, 0.0f, 0.0f, 0.0f, sy, 0.0f,  0.0f, 0.0f, sz);
}

math::mat3 math::mat3::rotate(const float angle, const vec3& axis) {
    return mat3();
}

float math::mat3::minimat_det(const int i, const mat3& m) {
    switch(i) {
    case 0:
        return m.data[4] * m.data[8] - m.data[5] * m.data[7];
    case 1:
        return m.data[3] * m.data[8] - m.data[5] * m.data[6];
    case 2:
        return m.data[3] * m.data[7] - m.data[4] * m.data[6];
    case 3:
        return m.data[1] * m.data[8] - m.data[2] * m.data[7];
    case 4:
        return m.data[0] * m.data[8] - m.data[2] * m.data[6];
    case 5:
        return m.data[0] * m.data[7] - m.data[1] * m.data[6];
    case 6:
        return m.data[1] * m.data[5] - m.data[2] * m.data[4];
    case 7:
        return m.data[0] * m.data[5] - m.data[2] * m.data[3];
    case 8:
        return m.data[0] * m.data[4] - m.data[1] * m.data[3];
    default:
        return 0.0f;
    }
}

const math::mat3 math::operator*(const float k, const mat3& m) {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = m.data[i] * k;
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

std::ostream& math::operator<<(std::ostream& os, const mat3& m) {
    os << "mat3[" << m.data[0] << ", " << m.data[3] << ", " << m.data[6] << "]" << std::endl;
    os << "    [" << m.data[1] << ", " << m.data[4] << ", " << m.data[7] << "]" << std::endl;
    os << "    [" << m.data[2] << ", " << m.data[5] << ", " << m.data[8] << "]";
    return os;
}

math::mat4::mat4() :
    data{ 0.0f } {}

math::mat4::mat4(float k) :
    data{ k, 0.0f, 0.0f, 0.0f,
        0.0f, k, 0.0f, 0.0f,
        0.0f, 0.0f, k, 0.0f,
        0.0f, 0.0f, 0.0f, k } {}

math::mat4::mat4(float v1, float v2, float v3, float v4,
    float v5, float v6, float v7, float v8,
    float v9, float v10, float v11, float v12,
    float v13, float v14, float v15, float v16) :
    data{ v1, v2, v3, v4,
        v5,v6,v7,v8,
        v9,v10,v11,v12,
        v13, v14,v15,v16 } {}

void math::mat4::clean() {
    for(int i = 0; i < 16; i++) {
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
    }
}

const float math::mat4::determinant() const {
    return 0.0f;
}

const math::mat4 math::mat4::transposed() const {
    return mat4(data[0], data[4], data[8], data[12],
        data[1], data[5], data[9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15]);
}

const math::mat4 math::mat4::inversed() const {
    return mat4();
}

math::mat4& math::mat4::operator=(const mat4& m) {
    for(int i = 0; i < 16; i++) data[i] = m.data[i];
    return *this;
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

float math::mat4::minimat_det(const int i, const mat4& m) {
    return 0.0f;
}

const math::mat4 math::operator*(const float k, const mat4& m) {
    return mat4();
}

std::ostream& math::operator<<(std::ostream& os, const mat4& m) {
    // TODO: insert return statement here
}