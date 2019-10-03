#include "vectors.h"

////////////////////////////////////////////////////////////////////////// VEC2

math::vec2::vec2() :
	x(0), y(0) {}

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
	x = y = 0;
}

const float math::vec2::quadrance() const {
	return x * x + y * y;
}

const float math::vec2::length() const {
	return sqrt(quadrance());
}

const math::vec2 math::vec2::normalize() {
	float len = length();
	if(len > 0) return vec2((1 / len) * x, (1 / len) * y);
	else return vec2();
}

math::vec2& math::vec2::operator=(const vec2& v) {
	x = v.x;
	y = v.y;
}

const math::vec2 math::vec2::operator-() const {
	return vec2(-x, -y);
}

math::vec2& math::vec2::operator+=(const vec2& v) {
	x += v.x;
	y += v.y;
}

math::vec2& math::vec2::operator-=(const vec2& v) {
	x -= v.x;
	y -= v.y;
}

math::vec2& math::vec2::operator*=(const float k) {
	x *= k;
	y *= k;
}

const math::vec2 math::vec2::operator+(const vec2& v) {
	return vec2(x + v.x, y + v.y);
}

const math::vec2 math::vec2::operator-(const vec2& v) {
	return vec2(x - v.x, y - v.y);
}

const math::vec2 math::vec2::operator*(const float k) {
	return vec2(x * k, y * k);
}

const bool math::vec2::operator==(const vec2& v) {
	return x == v.x && y == v.y;
}

const bool math::vec2::operator!=(const vec2& v) {
	return x != v.x || y != v.y;
}

const math::vec2 math::operator*(const float k, const vec2& v) {
	return vec2(v.x * k, v.y * k);
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
	x(0), y(0), z(0) {}

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
	x = y = z = 0;
}

const float math::vec3::quadrance() const {
	return x*x + y*y + z*z;
}

const float math::vec3::length() const {
	return sqrt(quadrance());
}

const math::vec3 math::vec3::normalize() {
	float len = length();
	if(len > 0) return vec3( (1 / len) * x, (1 / len) * y, (1 / len) * z );
	else return vec3();
}

math::vec3& math::vec3::operator=(const vec3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

const math::vec3 math::vec3::operator-() const {
	return vec3(-x,-y,-z);
}

math::vec3& math::vec3::operator+=(const vec3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

math::vec3& math::vec3::operator-=(const vec3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

math::vec3& math::vec3::operator*=(const float k) {
	x *= k;
	y *= k;
	z *= k;
}

const math::vec3 math::vec3::operator+(const vec3& v) {
	return vec3(x + v.x, y + v.y, z + v.z);
}

const math::vec3 math::vec3::operator-(const vec3& v) {
	return vec3(x - v.x, y - v.y, z - v.z);
}

const math::vec3 math::vec3::operator*(const float k) {
	return vec3(x * k, y * k, z * k);
}

const bool math::vec3::operator==(const vec3& v) {
	return x == v.x && y == v.y && z == v.z;
}

const bool math::vec3::operator!=(const vec3& v) {
	return x != v.x || y != v.y || z != v.z;
}

const math::vec3 math::operator*(const float k, const vec3& v) {
	return vec3(v.x * k, v.y * k, v.z * k);
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

vec4::vec4() :
	x(0), y(0), z(0), w(1) {}

vec4::vec4(const float k) :
	x(k), y(k), z(k), w(1) {}

vec4::vec4(const float x, const float y, const float z, const float w) :
	x(x), y(y), z(z), w(w) {}

vec4::vec4(const math::vec3& v) :
	x(v.x), y(v.y), z(v.z), w(1) {}

vec4::vec4(const vec4& v) :
	x(v.x), y(v.y), z(v.z), w(v.w) {}

float* vec4::data() {
	float ret[4] = { x, y, z, w };
	return ret;
}

void vec4::clean() {
	x = y = z = 0;
}

const float vec4::quadrance() const {
	return x*x + y*y + z*z;
}

const float vec4::length() const {
	return sqrt(quadrance());
}

const vec4 vec4::normalize() {
	float len = length();
	if(len > 0) return vec4((1/len) * x, (1/len) * y, (1/len) * z, w);
	else return vec4();
}

vec4& vec4::operator=(const vec4& v) {
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

const vec4 vec4::operator-() const {
	return vec4(-x, -y, -z, w);
}

vec4& vec4::operator+=(const vec4& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}

vec4& vec4::operator-=(const vec4& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

vec4& vec4::operator*=(const float k) {
	x *= k;
	y *= k;
	z *= k;
}

const vec4 vec4::operator+(const vec4& v) {
	return vec4(x + v.x, y + v.y, z + v.z, w);
}

const vec4 vec4::operator-(const vec4& v) {
	return vec4(x - v.x, y - v.y, z - v.z, w);
}

const vec4 vec4::operator*(const float k) {
	return vec4(x*k, y*k, z*k, w);
}

const bool vec4::operator==(const vec4& v) {
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

const bool vec4::operator!=(const vec4& v) {
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

const vec4 operator*(const float k, const vec4& v) {
	return vec4(v.x*k, v.y*k, v.z*k, v.w);
}

std::ostream& operator<<(std::ostream& os, const vec4& v) {
	os << "vec4(" << v.x << ", " << v.y << ", " << v.z << ", " << v.z << ")";
	return os;
}

std::istream& operator>>(std::istream& is, vec4& v) {
	is >> v.x;
	is >> v.y;
	is >> v.z;
	is >> v.w;
	return is;
}

////////////////////////////////////////////////////////////////////////// END