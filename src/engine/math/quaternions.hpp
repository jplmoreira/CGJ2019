#pragma once

#include <iostream>

#include "../include.hpp"

namespace engine {
    namespace math {
        struct qtrn {
            float t;
            vec3 v;

            qtrn();
            qtrn(const float t, const float x, const float y, const float z);
            qtrn(const float t, const vec3& v);
            qtrn(const vec3& axis, const float angle);

            void clean();
            const float quadrance() const;
            const float length() const;
            const qtrn normalized() const;
            const qtrn conjugate() const;
            const qtrn inverse() const;
            const vec3 axis() const;
            const float angle() const;
            friend const qtrn lerp(const qtrn& q1, const qtrn& q2, const float k);
            friend const qtrn slerp(const qtrn& q1, const qtrn& q2, const float k);

            qtrn& operator=(const qtrn& q);
            const qtrn operator+(const qtrn& q) const;
            const qtrn operator*(const qtrn& q) const;
            const qtrn operator*(const float k) const;
            const qtrn operator/(const float k) const;
            const bool operator==(const qtrn& q) const;
            const bool operator!=(const qtrn& q) const;
            friend std::ostream& operator<<(std::ostream& os, const qtrn& q);
        };
    }
}