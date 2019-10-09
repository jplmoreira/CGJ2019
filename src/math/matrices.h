#pragma once

#include <iostream>

#include "vectors.h"

namespace math {
    struct mat2;
    struct mat3;
    struct mat4;

    ////////////////////////////////////////////////////////////////////////// MAT2
    struct mat2 {
        float data[4];

        mat2();
        mat2(float k);
        mat2(float v1, float v2, float v3, float v4);

        void clean();
        const float determinant() const;
        const mat2 transposed() const;
        const mat2 inversed() const;

        mat2& operator=(const mat2& m);
        const mat2 operator-() const;
        mat2& operator+=(const mat2& m);
        mat2& operator-=(const mat2& m);
        mat2& operator*=(const float k);
        const mat2 operator+(const mat2& m) const;
        const mat2 operator-(const mat2& m) const;
        const mat2 operator*(const mat2& m) const;
        const vec2 operator*(const vec2& v) const;
        const mat2 operator*(const float k) const;
        friend const mat2 operator*(const float k, const mat2& m);
        const bool operator==(const mat2& m) const;
        const bool operator!=(const mat2& m) const;
        friend std::ostream& operator<<(std::ostream& os, const mat2& m);

        static mat2 identity_mat();
        static mat3 translate_mat(float dx, float dy);
        static mat2 scale_mat(float sx, float sy);
        static mat2 rotate(float angle);
    };

    ////////////////////////////////////////////////////////////////////////// MAT3
    struct mat3 {
        float data[9];

        mat3();
        mat3(float k);
        mat3(float v1, float v2, float v3,
            float v4, float v5, float v6,
            float v7, float v8, float v9);

        void clean();
        const float determinant() const;
        const mat3 transposed() const;
        const mat3 inversed() const;

        mat3& operator=(const mat3& m);
        const mat3 operator-() const;
        mat3& operator+=(const mat3& m);
        mat3& operator-=(const mat3& m);
        mat3& operator*=(const float k);
        const mat3 operator+(const mat3& m) const;
        const mat3 operator-(const mat3& m) const;
        const mat3 operator*(const mat3& m) const;
        const vec3 operator*(const vec3& v) const;
        const mat3 operator*(const float k) const;
        friend const mat3 operator*(const float k, const mat3& m);
        const bool operator==(const mat3& m) const;
        const bool operator!=(const mat3& m) const;
        friend std::ostream& operator<<(std::ostream& os, const mat3& m);

        static mat3 identity_mat();
        static mat4 translate_mat(float dx, float dy, float dz);
        static mat3 scale_mat(float sx, float sy, float sz);
        static mat3 rotate(float angle, vec3& axis);
    };

    ////////////////////////////////////////////////////////////////////////// MAT4
    struct mat4 {
        float data[16];

        mat4();
        mat4(float k);
        mat4(float v1, float v2, float v3, float v4,
            float v5, float v6, float v7, float v8,
            float v9, float v10, float v11, float v12,
            float v13, float v14, float v15, float v16);

        void clean();
        const float determinant() const;
        const mat4 transposed() const;
        const mat4 inversed() const;

        mat4& operator=(const mat4& m);
        const mat4 operator-() const;
        mat4& operator+=(const mat4& m);
        mat4& operator-=(const mat4& m);
        mat4& operator*=(const float k);
        const mat4 operator+(const mat4& m) const;
        const mat4 operator-(const mat4& m) const;
        const mat4 operator*(const mat4& m) const;
        const vec4 operator*(const vec4& v) const;
        const mat4 operator*(const float k) const;
        friend const mat4 operator*(const float k, const mat4& m);
        const bool operator==(const mat4& m) const;
        const bool operator!=(const mat4& m) const;
        friend std::ostream& operator<<(std::ostream& os, const mat4& m);

        static mat4 identity_mat();
        static mat4 translate_mat(float dx, float dy, float dz);
        static mat4 scale_mat(float sx, float sy, float sz);
        static mat4 rotate(float angle, vec3& axis);
    };
}