#include "matrices.h"

math::mat2::mat2() {}

math::mat2::mat2(float k) {}

math::mat2::mat2(float v1, float v2, float v3, float v4) {}

void math::mat2::clean() {}

const float math::mat2::determinant() const {
    return 0.0f;
}

const math::mat2 math::mat2::transposed() const {
    return mat2();
}

const math::mat2 math::mat2::inversed() const {
    return mat2();
}

math::mat2& math::mat2::operator=(const mat2& m) {
    // TODO: insert return statement here
}

const math::mat2 math::mat2::operator-() const {
    return mat2();
}

math::mat2& math::mat2::operator+=(const mat2& m) {
    // TODO: insert return statement here
}

math::mat2& math::mat2::operator-=(const mat2& m) {
    // TODO: insert return statement here
}

math::mat2& math::mat2::operator*=(const float k) {
    // TODO: insert return statement here
}

const math::mat2 math::mat2::operator+(const mat2& m) const {
    return mat2();
}

const math::mat2 math::mat2::operator-(const mat2& m) const {
    return mat2();
}

const math::mat2 math::mat2::operator*(const mat2& m) const {
    return mat2();
}

const math::vec2 math::mat2::operator*(const vec2& v) const {
    return vec2();
}

const math::mat2 math::mat2::operator*(const float k) const {
    return mat2();
}

const bool math::mat2::operator==(const mat2& m) const {
    return false;
}

const bool math::mat2::operator!=(const mat2& m) const {
    return false;
}

math::mat2 math::mat2::identity_mat() {
    return mat2();
}

math::mat3 math::mat2::translate_mat(float dx, float dy) {
    return mat3();
}

math::mat2 math::mat2::scale_mat(float sx, float sy) {
    return mat2();
}

math::mat2 math::mat2::rotate(float angle) {
    return mat2();
}

const math::mat2 math::operator*(const float k, const mat2& m) {
    return mat2();
}

std::ostream& math::operator<<(std::ostream& os, const mat2& m) {
    // TODO: insert return statement here
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
