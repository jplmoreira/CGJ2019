#include <iostream>

#include "test.h"
#include "../math/vectors.h"

void vec_tests() {
	math::vec3 v1 = math::vec3(1, 0, 0);
	math::vec3 v2 = math::vec3(0, 1, 0);
	math::vec3 v3 = math::vec3(0, 0, 1);

	std::cout << "TEST 1\n" << std::endl;
	math::vec3 res = v1 + v2 + v3;
	std::cout << "Expected: vec3(1, 1, 1)\nResult: " << res << std::endl << std::endl;

	std::cout << "TEST 2\n" << std::endl;
	res = v1 - v2;
	std::cout << "Expected: vec3(1, -1, 0)\nResult: " << res << std::endl << std::endl;

	std::cout << "TEST 3\n" << std::endl;
	res *= 3;
	std::cout << "Expected: vec3(3, -3, 0)\nResult: " << res << std::endl << std::endl;

	std::cout << "TEST 4\n" << std::endl;
	std::cout << "Expected: vec3(1, 0, 0)\nResult: " << (v1 * 8).normalize() << std::endl << std::endl;

	std::cout << "TEST 5\n" << std::endl;
	std::cout << "Expected: vec3(1, 0, 0)\nResult: " << v2.cross(v3) << std::endl << std::endl;

	std::cout << "TEST 6\n" << std::endl;
	std::cout << "Expected: 0\nResult: " << v2.dot(v3) << std::endl;
}