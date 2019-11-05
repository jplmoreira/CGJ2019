#pragma once

#include "../include.hpp"

engine::math::vec4 purple(163.0f / 255.0f, 92.0f / 255.0f, 189.0f / 255.0f, 1.0f);
engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);
engine::math::vec4 red(223.0f / 255.0f, 86.0f / 255.0f, 86.0f / 255.0f, 1.0f);
engine::math::vec4 blue(86.0f / 255.0f, 116.0f / 255.0f, 223.0f / 255.0f, 1.0f);
engine::math::vec4 green(62.0f / 255.0f, 137.0f / 255.0f, 98.0f / 255.0f, 1.0f);
engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);
engine::math::vec4 teal(19.0f / 255.0f, 111.0f / 255.0f, 114.0f / 255.0f, 1.0f);

float v_triangle[3][4] = {
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f }
};
GLushort i_triangle[3] = { 0,1,2 };

float v_square[4][4] = {
    { 0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.0f, 1.0f },
    { 0.5f, -0.5f, 0.0f, 1.0f }
};

GLushort i_square[6] = { 0, 1, 2, 0, 2, 3 };

float v_para[4][4] = {
    { 0.25f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.5f, 0.0f, 1.0f },
    { -0.25f, -0.5f, 0.0f, 1.0f },
    { 0.5f, -0.5f, 0.0f, 1.0f }
};

GLushort i_para[6] = { 0, 1, 2, 0, 2, 3 };

namespace engine {
    namespace geometry {
        template<std::size_t SIZE_V, std::size_t SIZE_I>
        object create_object(float(&vertices)[SIZE_V][4],
            GLushort(&indices)[SIZE_I], engine::math::vec4 color) {
            GLuint vbo[3];
            object o;
            o.num_indexes = SIZE_I;

            glGenVertexArrays(1, &o.vao);
            glBindVertexArray(o.vao);
            {
                glGenBuffers(3, vbo);

                glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
                {
                    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                    glEnableVertexAttribArray(ATTR::VERTICES);
                    glVertexAttribPointer(ATTR::VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
                }
                glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
                {
                    GLsizei offset = sizeof(float) * 4;
                    glBufferData(GL_ARRAY_BUFFER, offset * SIZE_V, nullptr, GL_STATIC_DRAW);
                    for(int i = 0; i < SIZE_V; i++) {
                        glBufferSubData(GL_ARRAY_BUFFER, i * offset, offset, color.data());
                    }
                    glEnableVertexAttribArray(ATTR::COLORS);
                    glVertexAttribPointer(ATTR::COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
                }
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
                {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
                }
            }
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            return o;
        }
    }
}