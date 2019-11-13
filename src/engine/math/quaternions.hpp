#pragma once

#include <iostream>

#include "../include.hpp"

namespace engine {
    namespace math {
        struct quaternion {
            float t;
            vec3 v;

            quaternion();
            quaternion(const float t, const float x, const float y, const float z);
            quaternion(const float t, const vec3& v);
            quaternion(const vec3& axis, const float angle);

            void clean();
            const float quadrance() const;
            const float length() const;
            const quaternion normalized() const;
            const quaternion conjugate() const;
            const quaternion inverse() const;
            const vec3 axis() const;
            const float angle() const;

            quaternion& operator=(const quaternion& q);
            const quaternion operator+(const quaternion& q) const;
            const quaternion operator*(const quaternion& q) const;
            const quaternion operator*(const float k) const;
            const quaternion operator/(const float k) const;
            const bool operator==(const quaternion& q) const;
            const bool operator!=(const quaternion& q) const;
            friend std::ostream& operator<<(std::ostream& os, const quaternion& q);
        };
    }
}