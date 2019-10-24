#include "geometry.hpp"

#include <GL/glew.h>

float right_triangle_v[3][4] = {
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f }
};

GLushort right_triangle_i[3] = { 0, 1, 2 };

float square_v[4][4] = {
    { 0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.0f, 1.0f },
    { 0.5f, -0.5f, 0.0f, 1.0f }
};

GLushort square_i[6] = { 0, 1, 2, 0, 2, 3 };

float para_v[4][4] = {
    { 0.0f, 0.5f, 0.0f, 1.0f },
    { -1.0f, 0.5f, 0.0f, 1.0f },
    { 0.0f, -0.5f, 0.0f, 1.0f },
    { 1.0f, -0.5f, 0.0f, 1.0f }
};

GLushort para_i[6] = { 0, 1, 2, 0, 2, 3 };

engine::objects::object engine::objects::create_triangle(const math::vec4& color) {
    GLuint vbo[3];
    
    object o;
    o.color = engine::math::vec4(color);
    o.num_indexes = 3;
    
    glGenVertexArrays(1, &o.vao);
    glBindVertexArray(o.vao);
    {
        glGenBuffers(3, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(right_triangle_v), right_triangle_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::VERTICES);
            glVertexAttribPointer(ATTR::VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
            
        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        {
            float color_array[3][4] = {
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::COLORS);
            glVertexAttribPointer(ATTR::COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(right_triangle_i), right_triangle_i, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return o;
}

engine::objects::object engine::objects::create_square(const math::vec4& color) {
    GLuint vbo[3];

    object o;
    o.color = engine::math::vec4(color);
    o.num_indexes = 6;

    glGenVertexArrays(1, &o.vao);
    glBindVertexArray(o.vao);
    {
        glGenBuffers(3, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(square_v), square_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::VERTICES);
            glVertexAttribPointer(ATTR::VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);

        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        {
            float color_array[3][4] = {
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::COLORS);
            glVertexAttribPointer(ATTR::COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(square_i), square_i, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return o;
}

engine::objects::object engine::objects::create_parallelogram(const math::vec4& color) {
    GLuint vbo[3];

    object o;
    o.color = engine::math::vec4(color);
    o.num_indexes = 6;

    glGenVertexArrays(1, &o.vao);
    glBindVertexArray(o.vao);
    {
        glGenBuffers(3, vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(para_v), para_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::VERTICES);
            glVertexAttribPointer(ATTR::VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);

        }
        glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
        {
            float color_array[3][4] = {
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_array), color_array, GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::COLORS);
            glVertexAttribPointer(ATTR::COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(para_i), para_i, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return o;
}
