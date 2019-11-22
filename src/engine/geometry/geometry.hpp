#pragma once

#include "../include.hpp"

float v_triangle[3][3] = {
    { 0.0f, 0.0f, 0.0f},
    { 1.0f, 0.0f, 0.0f  },
    { 0.0f, 1.0f, 0.0f }
};
GLushort i_triangle[3] = { 0,1,2 };

float v_square[4][3] = {
    { 0.5f, 0.5f, 0.0f },
    { -0.5f, 0.5f, 0.0f },
    { -0.5f, -0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f }
};

GLushort i_square[6] = { 0, 1, 2, 0, 2, 3 };

float v_para[4][3] = {
    { 0.25f, 0.5f, 0.0f },
    { -0.5f, 0.5f, 0.0f },
    { -0.25f, -0.5f, 0.0f },
    { 0.5f, -0.5f, 0.0f }
};

GLushort i_para[6] = { 0, 1, 2, 0, 2, 3 };