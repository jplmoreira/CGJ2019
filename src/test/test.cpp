#include <iostream>
#include <ctime>
#include <vector>

#include "test.hpp"
#include "../engine/math/vectors.hpp"
#include "../engine/math/matrices.hpp"
#include "../engine/math/mat_fact.hpp"

inline float random_float_1() {
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 2.0f) - 1.0f;
}

void vec_tests() {
    engine::math::vec3 v1 = engine::math::vec3(1, 0, 0);
    engine::math::vec3 v2 = engine::math::vec3(0, 1, 0);
    engine::math::vec3 v3 = engine::math::vec3(0, 0, 1);

    std::cout << "TEST 1\n" << std::endl;
    engine::math::vec3 res = v1 + v2 + v3;
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
        engine::math::vec3 i = engine::math::vec3(random_float_1(), random_float_1(), random_float_1());
        engine::math::vec3 j = engine::math::vec3(random_float_1(), random_float_1(), random_float_1());
        engine::math::vec3 k = engine::math::vec3(random_float_1(), random_float_1(), random_float_1());
        engine::math::vec3 right = cross(i, cross(j, k));
        engine::math::vec3 left = j * (dot(i, k)) - k * (dot(i, j));

        std::cout << "Test #" << x + 1 << " - " << (right == left) << std::endl;
    }

    engine::math::vec3 i = engine::math::vec3();
    engine::math::vec3 j = engine::math::vec3(random_float_1(), random_float_1(), random_float_1());
    engine::math::vec3 k = engine::math::vec3(random_float_1(), random_float_1(), random_float_1());
    engine::math::vec3 right = cross(i, cross(j, k));
    engine::math::vec3 left = j * (dot(i, k)) - k * (dot(i, j));
    std::cout << "Test #10 - " << (right == left) << std::endl;
}

void mat_tests() {

    std::cout << "MATRIX TESTS" << std::endl;

    engine::math::mat4 res = engine::math::mat4::identity_mat();
    engine::math::mat4 mat1 = engine::math::mat_fact::translate(1.5f, 0.5f, 1.0f);
    engine::math::mat4 mat2 = engine::math::mat_fact::translate(0.5f, 1.0f, 0.0f);

    res = mat2 * mat1 * res;
    engine::math::mat4 cmp = engine::math::mat4::identity_mat();
    cmp.data[12] = 2.0f;
    cmp.data[13] = 1.5f;
    cmp.data[14] = 1.0f;

    std::cout << "mult test - " << (res == cmp) << std::endl;

    engine::math::vec4 point = engine::math::vec4(1.0f);
    mat1 = engine::math::mat_fact::translate(1.0f, 0.0f, 0.0f);
    point = mat1 * point;

    std::cout << "vec mult test - " << (point == engine::math::vec4(2.0f, 1.0f, 1.0f, 1.0f)) << std::endl;

    engine::math::mat3 inv = engine::math::mat3(1.0f, 0.0f, 5.0f, 2.0f, 1.0f, 6.0f, 3.0f, 4.0f, 0.0f);
    inv = inv.inversed();

    std::cout << "inverse - " << (inv == engine::math::mat3(-24.0f, 20.0f, -5.0f, 18.0f, -15.0f, 4.0f, 5.0f, -4.0f, 1.0f)) << std::endl;
}

void mat_eval() {
    std::vector<engine::math::vec4> vs = { engine::math::vec4(2.0f, 0.0f, 0.0f, 1.0f), engine::math::vec4(0.0f, 3.0f, 0.0f, 1.0f), engine::math::vec4(0.0f, 0.0f, 4.0f, 1.0f) };
    const float angle = 90.0f;

    for(const engine::math::vec4& v1 : vs) {
        for(const engine::math::vec4& v2 : vs) {
            engine::math::mat4 rot = engine::math::mat_fact::rodr_rot(angle, engine::math::vec3(v1.x, v1.y, v1.z));
            engine::math::vec4 res = rot * v2;
            std::cout << "Rotation of " << v2 << " around " << v1 << ":" << std::endl << "\t" << res << std::endl;
        }
    }
}