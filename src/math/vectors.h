#pragma once

#include <iostream>

namespace math {
	struct vec2;
	struct vec3;
	struct vec4;

////////////////////////////////////////////////////////////////////////// VEC2

	struct vec2 {
		float x, y;

		vec2();
		vec2(const float k);
		vec2(const float x, const float y);
		vec2(const vec2& v);
		float* data();
		void clean();
		const float quadrance() const;
		const float length() const;
		const vec2 normalize();
		vec2& operator=(const vec2& v);
		const vec2 operator-() const;
		vec2& operator+=(const vec2& v);
		vec2& operator-=(const vec2& v);
		vec2& operator*=(const float k);
		const vec2 operator+(const vec2& v);
		const vec2 operator-(const vec2& v);
		const vec2 operator*(const float k);
		friend const vec2 operator*(const float k, const vec2& v);
		const bool operator==(const vec2& v);
		const bool operator!=(const vec2& v);
		friend std::ostream& operator<<(std::ostream& os, const vec2& v);
		friend std::istream& operator>>(std::istream& is, vec2& v);
	};

////////////////////////////////////////////////////////////////////////// VEC3

	struct vec3 {
		float x, y, z;

		vec3();
		vec3(const float k);
		vec3(const float x, const float y, const float z);
		vec3(const vec3& v);
		float* data();
		void clean();
		const float quadrance() const;
		const float length() const;
		const vec3 normalize();
		vec3& operator=(const vec3& v);
		const vec3 operator-() const;
		vec3& operator+=(const vec3& v);
		vec3& operator-=(const vec3& v);
		vec3& operator*=(const float k);
		const vec3 operator+(const vec3& v);
		const vec3 operator-(const vec3& v);
		const vec3 operator*(const float k);
		friend const vec3 operator*(const float k, const vec3& v);
		const bool operator==(const vec3& v);
		const bool operator!=(const vec3& v);
		friend std::ostream& operator<<(std::ostream& os, const vec3& v);
		friend std::istream& operator>>(std::istream& is, vec3& v);
	};
}

////////////////////////////////////////////////////////////////////////// VEC4

struct vec4 {
	float x, y, z, w;

	vec4();
	vec4(const float k);
	vec4(const float x, const float y, const float z, const float w);
	vec4(const math::vec3& v);
	vec4(const vec4& v);
	float* data();
	void clean();
	const float quadrance() const;
	const float length() const;
	const vec4 normalize();
	vec4& operator=(const vec4& v);
	const vec4 operator-() const;
	vec4& operator+=(const vec4& v);
	vec4& operator-=(const vec4& v);
	vec4& operator*=(const float k);
	const vec4 operator+(const vec4& v);
	const vec4 operator-(const vec4& v);
	const vec4 operator*(const float k);
	friend const vec4 operator*(const float k, const vec4& v);
	const bool operator==(const vec4& v);
	const bool operator!=(const vec4& v);
	friend std::ostream& operator<<(std::ostream& os, const vec4& v);
	friend std::istream& operator>>(std::istream& is, vec4& v);
};

////////////////////////////////////////////////////////////////////////// END