#include "matrices.hpp"

#define THRESHOLD 0.00001f

////////////////////////////////////////////////////////////////////////// MAT2

engine::math::mat2::mat2() :
    data{ 0.0f } {}

engine::math::mat2::mat2(float k) :
    data{ k, 0.0f, 0.0f, k } {}

engine::math::mat2::mat2(float v1, float v2, float v3, float v4) :
    data{ v1, v2, v3, v4 } {}

engine::math::mat2::mat2(const mat2& m) :
    data{ m.data[0], m.data[1], m.data[2], m.data[3] } {}

void engine::math::mat2::clean() {
    for(int i = 0; i < 4; i++)
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
}

const float engine::math::mat2::determinant() const {
    return data[0] * data[3] - data[1] * data[2];
}

const engine::math::mat2 engine::math::mat2::transposed() const {
    return mat2(data[0], data[2], data[1], data[3]);
}

const engine::math::mat2 engine::math::mat2::inversed() const {
    float det = determinant();
    if(det > 0) return mat2(data[3] / det, -data[1] / det, -data[2] / det, data[0] / det);
    return mat2(*this);
}

engine::math::mat2& engine::math::mat2::operator=(const mat2& m) {
    data[0] = m.data[0];
    data[1] = m.data[1];
    data[2] = m.data[2];
    data[3] = m.data[3];

    return *this;
}

const engine::math::mat2 engine::math::mat2::operator-() const {
    return mat2(-data[0], -data[1], -data[2], -data[3]);
}

engine::math::mat2& engine::math::mat2::operator+=(const mat2& m) {
    data[0] += m.data[0];
    data[1] += m.data[1];
    data[2] += m.data[2];
    data[3] += m.data[3];

    return *this;
}

engine::math::mat2& engine::math::mat2::operator-=(const mat2& m) {
    data[0] -= m.data[0];
    data[1] -= m.data[1];
    data[2] -= m.data[2];
    data[3] -= m.data[3];

    return *this;
}

engine::math::mat2& engine::math::mat2::operator*=(const float k) {
    data[0] *= k;
    data[1] *= k;
    data[2] *= k;
    data[3] *= k;

    return *this;
}

const engine::math::mat2 engine::math::mat2::operator+(const mat2& m) const {
    return mat2(data[0] + m.data[0], data[1] + m.data[1], data[2] + m.data[2], data[3] + m.data[3]);
}

const engine::math::mat2 engine::math::mat2::operator-(const mat2& m) const {
    return mat2(data[0] - m.data[0], data[1] - m.data[1], data[2] - m.data[2], data[3] - m.data[3]);
}

const engine::math::mat2 engine::math::mat2::operator*(const mat2& m) const {
    return mat2(data[0] * m.data[0], data[1] * m.data[1], data[2] * m.data[2], data[3] * m.data[3]);
}

const engine::math::vec2 engine::math::mat2::operator*(const vec2& v) const {
    float x = data[0] * v.x + data[2] * v.y;
    float y = data[1] * v.x + data[3] * v.y;
    return vec2(x, y);
}

const engine::math::mat2 engine::math::mat2::operator*(const float k) const {
    return mat2(data[0] * k, data[1] * k, data[2] * k, data[3] * k);
}

const bool engine::math::mat2::operator==(const mat2& m) const {
    for(int i = 0; i < 4; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return false;
    return true;
}

const bool engine::math::mat2::operator!=(const mat2& m) const {
    for(int i = 0; i < 4; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return true;
    return false;
}

engine::math::mat2 engine::math::mat2::identity_mat() {
    return mat2(1.0f);
}

const engine::math::mat2 engine::math::operator*(const float k, const mat2& m) {
    return m * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const mat2& m) {
    os << "mat2[" << m.data[0] << ", " << m.data[2] << "]" << std::endl;
    os << "    [" << m.data[1] << ", " << m.data[3] << "]";
    return os;
}

////////////////////////////////////////////////////////////////////////// MAT3

engine::math::mat3::mat3() :
    data{ 0.0f } {}

engine::math::mat3::mat3(float k) :
    data{ k, 0.0f, 0.0f,
    0.0f, k, 0.0f,
    0.0f, 0.0f, k } {}

engine::math::mat3::mat3(float v1, float v2, float v3,
    float v4, float v5, float v6,
    float v7, float v8, float v9) :
    data{ v1,v2,v3,v4,v5,v6,v7,v8,v9 } {}

void engine::math::mat3::clean() {
    for(int i = 0; i < 9; i++)
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
}

const float engine::math::mat3::determinant() const {
    return data[0] * minimat_det(0, *this) - data[3] * minimat_det(3, *this) + data[6] * minimat_det(6, *this);
}

const engine::math::mat3 engine::math::mat3::transposed() const {
    return mat3(data[0], data[3], data[6],
        data[1], data[4], data[7],
        data[2], data[5], data[8]);
}

const engine::math::mat3 engine::math::mat3::inversed() const {
    float det = this->determinant();
    if(det == 0)
        throw std::exception("Impossible to invert matrix");

    mat3 trans = this->transposed();

    mat3 adj = mat3(minimat_det(0, trans), minimat_det(1, trans), minimat_det(2, trans), minimat_det(3, trans),
        minimat_det(4, trans), minimat_det(5, trans), minimat_det(6, trans), minimat_det(7, trans), minimat_det(8, trans));

    mat3 inv = adj / det;
    inv.data[1] *= -1;
    inv.data[3] *= -1;
    inv.data[5] *= -1;
    inv.data[7] *= -1;

    return inv;
}

engine::math::mat3& engine::math::mat3::operator=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] = m.data[i];
    return *this;
}

const engine::math::mat3 engine::math::mat3::operator-() const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = -data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

engine::math::mat3& engine::math::mat3::operator+=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] += m.data[i];
    return *this;
}

engine::math::mat3& engine::math::mat3::operator-=(const mat3& m) {
    for(int i = 0; i < 9; i++) data[i] -= m.data[i];
    return *this;
}

engine::math::mat3& engine::math::mat3::operator*=(const float k) {
    for(int i = 0; i < 9; i++) data[i] *= k;
    return *this;
}

const engine::math::mat3 engine::math::mat3::operator+(const mat3& m) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] + m.data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const engine::math::mat3 engine::math::mat3::operator-(const mat3& m) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] - m.data[i];
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const engine::math::mat3 engine::math::mat3::operator*(const mat3& m) const {
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

const engine::math::vec3 engine::math::mat3::operator*(const vec3& v) const {
    float x = data[0] * v.x + data[3] * v.y + data[6] * v.z;
    float y = data[1] * v.x + data[4] * v.y + data[7] * v.z;
    float z = data[2] * v.x + data[5] * v.y + data[8] * v.z;

    return vec3(x, y, z);
}

const engine::math::mat3 engine::math::mat3::operator*(const float k) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] * k;
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const engine::math::mat3 engine::math::mat3::operator/(const float k) const {
    float aux[9] = { 0.0f };
    for(int i = 0; i < 9; i++) aux[i] = data[i] / k;
    return mat3(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7], aux[8]);
}

const bool engine::math::mat3::operator==(const mat3& m) const {
    for(int i = 0; i < 4; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return false;
    return true;
}

const bool engine::math::mat3::operator!=(const mat3& m) const {
    for(int i = 0; i < 4; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return true;
    return false;
}

engine::math::mat3 engine::math::mat3::identity_mat() {
    return mat3(1.0f);
}

float engine::math::mat3::minimat_det(const int i, const mat3& m) {
    switch(i) {
    case 0:
        return mat2(m.data[4], m.data[5], m.data[7], m.data[8]).determinant();
    case 1:
        return mat2(m.data[3], m.data[5], m.data[6], m.data[8]).determinant();
    case 2:
        return mat2(m.data[3], m.data[4], m.data[6], m.data[7]).determinant();
    case 3:
        return mat2(m.data[1], m.data[2], m.data[7], m.data[8]).determinant();
    case 4:
        return mat2(m.data[0], m.data[2], m.data[6], m.data[8]).determinant();
    case 5:
        return mat2(m.data[0], m.data[1], m.data[6], m.data[7]).determinant();
    case 6:
        return mat2(m.data[1], m.data[2], m.data[4], m.data[5]).determinant();
    case 7:
        return mat2(m.data[0], m.data[2], m.data[3], m.data[5]).determinant();
    case 8:
        return mat2(m.data[0], m.data[1], m.data[3], m.data[4]).determinant();
    default:
        return 0.0f;
    }
}

const engine::math::mat3 engine::math::operator*(const float k, const mat3& m) {
    return m * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const mat3& m) {
    os << "mat3[" << m.data[0] << ", " << m.data[3] << ", " << m.data[6] << "]" << std::endl;
    os << "    [" << m.data[1] << ", " << m.data[4] << ", " << m.data[7] << "]" << std::endl;
    os << "    [" << m.data[2] << ", " << m.data[5] << ", " << m.data[8] << "]";
    return os;
}

////////////////////////////////////////////////////////////////////////// MAT4

engine::math::mat4::mat4() :
    data{ 0.0f } {}

engine::math::mat4::mat4(float k) :
    data{ k, 0.0f, 0.0f, 0.0f,
        0.0f, k, 0.0f, 0.0f,
        0.0f, 0.0f, k, 0.0f,
        0.0f, 0.0f, 0.0f, k } {}

engine::math::mat4::mat4(float v1, float v2, float v3, float v4,
    float v5, float v6, float v7, float v8,
    float v9, float v10, float v11, float v12,
    float v13, float v14, float v15, float v16) :
    data{ v1, v2, v3, v4,
        v5,v6,v7,v8,
        v9,v10,v11,v12,
        v13, v14,v15,v16 } {}

engine::math::mat4::mat4(mat3& m) :
    data{ m.data[0], m.data[1], m.data[2], 0.0f,
    m.data[3], m.data[4], m.data[5], 0.0f,
    m.data[6], m.data[7], m.data[8], 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f } {}

void engine::math::mat4::clean() {
    for(int i = 0; i < 16; i++)
        if(std::fabs(data[i]) < THRESHOLD) data[i] = 0.0f;
}

const engine::math::mat4 engine::math::mat4::transposed() const {
    return mat4(data[0], data[4], data[8], data[12],
        data[1], data[5], data[9], data[13],
        data[2], data[6], data[10], data[14],
        data[3], data[7], data[11], data[15]);
}

engine::math::mat4& engine::math::mat4::operator=(const mat4& m) {
    for(int i = 0; i < 16; i++) data[i] = m.data[i];
    return *this;
}

const engine::math::mat4 engine::math::mat4::operator-() const {
    float aux[16] = { 0.0f };
    for(int i = 0; i < 16; i++) aux[i] = -data[i];
    return mat4(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7],
        aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
}

engine::math::mat4& engine::math::mat4::operator+=(const mat4& m) {
    for(int i = 0; i < 16; i++) data[i] += m.data[i];
    return *this;
}

engine::math::mat4& engine::math::mat4::operator-=(const mat4& m) {
    for(int i = 0; i < 16; i++) data[i] -= m.data[i];
    return *this;
}

engine::math::mat4& engine::math::mat4::operator*=(const float k) {
    for(int i = 0; i < 16; i++) data[i] *= k;
    return *this;
}

const engine::math::mat4 engine::math::mat4::operator+(const mat4& m) const {
    float aux[16] = { 0.0f };
    for(int i = 0; i < 16; i++) aux[i] = data[i] + m.data[i];
    return mat4(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7],
        aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
}

const engine::math::mat4 engine::math::mat4::operator-(const mat4& m) const {
    float aux[16] = { 0.0f };
    for(int i = 0; i < 16; i++) aux[i] = data[i] - m.data[i];
    return mat4(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7],
        aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
}

const engine::math::mat4 engine::math::mat4::operator*(const mat4& m) const {
    float r0 = data[0] * m.data[0] + data[4] * m.data[1] + data[8] * m.data[2] + data[12] * m.data[3];
    float r1 = data[1] * m.data[0] + data[5] * m.data[1] + data[9] * m.data[2] + data[13] * m.data[3];
    float r2 = data[2] * m.data[0] + data[6] * m.data[1] + data[10] * m.data[2] + data[14] * m.data[3];
    float r3 = data[3] * m.data[0] + data[7] * m.data[1] + data[11] * m.data[2] + data[15] * m.data[3];

    float r4 = data[0] * m.data[4] + data[4] * m.data[5] + data[8] * m.data[6] + data[12] * m.data[7];
    float r5 = data[1] * m.data[4] + data[5] * m.data[5] + data[9] * m.data[6] + data[13] * m.data[7];
    float r6 = data[2] * m.data[4] + data[6] * m.data[5] + data[10] * m.data[6] + data[14] * m.data[7];
    float r7 = data[3] * m.data[4] + data[7] * m.data[5] + data[11] * m.data[6] + data[15] * m.data[7];

    float r8 = data[0] * m.data[8] + data[4] * m.data[9] + data[8] * m.data[10] + data[12] * m.data[11];
    float r9 = data[1] * m.data[8] + data[5] * m.data[9] + data[9] * m.data[10] + data[13] * m.data[11];
    float r10 = data[2] * m.data[8] + data[6] * m.data[9] + data[10] * m.data[10] + data[14] * m.data[11];
    float r11 = data[3] * m.data[8] + data[7] * m.data[9] + data[11] * m.data[10] + data[15] * m.data[11];

    float r12 = data[0] * m.data[12] + data[4] * m.data[13] + data[8] * m.data[14] + data[12] * m.data[15];
    float r13 = data[1] * m.data[12] + data[5] * m.data[13] + data[9] * m.data[14] + data[13] * m.data[15];
    float r14 = data[2] * m.data[12] + data[6] * m.data[13] + data[10] * m.data[14] + data[14] * m.data[15];
    float r15 = data[3] * m.data[12] + data[7] * m.data[13] + data[11] * m.data[14] + data[15] * m.data[15];

    return mat4(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15);
}

const engine::math::vec4 engine::math::mat4::operator*(const vec4& v) const {
    float x = data[0] * v.x + data[4] * v.y + data[8] * v.z + data[12] * v.w;
    float y = data[1] * v.x + data[5] * v.y + data[9] * v.z + data[13] * v.w;
    float z = data[2] * v.x + data[6] * v.y + data[10] * v.z + data[14] * v.w;
    float w = data[3] * v.x + data[7] * v.y + data[11] * v.z + data[15] * v.w;

    return vec4(x, y, w, z);
}

const engine::math::mat4 engine::math::mat4::operator*(const float k) const {
    float aux[16] = { 0.0f };
    for(int i = 0; i < 16; i++) aux[i] = data[i] * k;
    return mat4(aux[0], aux[1], aux[2], aux[3], aux[4], aux[5], aux[6], aux[7],
        aux[8], aux[9], aux[10], aux[11], aux[12], aux[13], aux[14], aux[15]);
}

const bool engine::math::mat4::operator==(const mat4& m) const {
    for(int i = 0; i < 16; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return false;
    return true;
}

const bool engine::math::mat4::operator!=(const mat4& m) const {
    for(int i = 0; i < 16; i++)
        if(std::fabs(data[i] - m.data[i]) >= THRESHOLD) return true;
    return false;
}

engine::math::mat4 engine::math::mat4::identity_mat() {
    return mat4(1.0f);
}

const engine::math::mat4 engine::math::operator*(const float k, const mat4& m) {
    return m * k;
}

std::ostream& engine::math::operator<<(std::ostream& os, const mat4& m) {
    os << "mat4[" << m.data[0] << ", " << m.data[4] << ", " << m.data[8] << ", " << m.data[12] << "]" << std::endl;
    os << "    [" << m.data[1] << ", " << m.data[5] << ", " << m.data[9] << ", " << m.data[13] << "]" << std::endl;
    os << "    [" << m.data[2] << ", " << m.data[6] << ", " << m.data[10] << ", " << m.data[14] << "]" << std::endl;
    os << "    [" << m.data[3] << ", " << m.data[7] << ", " << m.data[11] << ", " << m.data[15] << "]";
    return os;
}

////////////////////////////////////////////////////////////////////////// END