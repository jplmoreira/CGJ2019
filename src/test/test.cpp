#include <iostream>
#include <ctime>

#include "test.hpp"
#include "../math/vectors.hpp"

inline float random_float_1() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f) - 1.0f;
}

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
    std::cout << "Expected: vec3(1, 0, 0)\nResult: " << (v1 * 8).normalized() << std::endl << std::endl;

    std::cout << "TEST 5\n" << std::endl;
    std::cout << "Expected: vec3(1, 0, 0)\nResult: " << cross(v2, v3) << std::endl << std::endl;

    std::cout << "TEST 6\n" << std::endl;
    std::cout << "Expected: 0\nResult: " << dot(v2, v3) << std::endl;
}

void vec_eval() {
    srand(static_cast<unsigned> (time(0)));

    for(int x = 0; x < 9; x++) {
        math::vec3 i = math::vec3(random_float_1(), random_float_1(), random_float_1());
        math::vec3 j = math::vec3(random_float_1(), random_float_1(), random_float_1());
        math::vec3 k = math::vec3(random_float_1(), random_float_1(), random_float_1());
        math::vec3 right = cross(i, cross(j, k));
        math::vec3 left = j * (dot(i, k)) - k * (dot(i, j));

        std::cout << "Test #" << x + 1 << " - " << (right == left) << std::endl;
    }

    math::vec3 i = math::vec3();
    math::vec3 j = math::vec3(random_float_1(), random_float_1(), random_float_1());
    math::vec3 k = math::vec3(random_float_1(), random_float_1(), random_float_1());
    math::vec3 right = cross(i, cross(j, k));
    math::vec3 left = j * (dot(i, k)) - k * (dot(i, j));
    std::cout << "Test #10 - " << (right == left) << std::endl;
}