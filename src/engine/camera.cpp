#include <cmath>

#include "camera.hpp"
#include "shader.hpp"

std::shared_ptr<engine::camera> engine::camera::instance;

void engine::camera::create_block() {
    glGenBuffers(1, &ubo_id);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
    {
        glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 16 * 2, 0, GL_STREAM_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, shader::get_instance()->get_block_ptr(), ubo_id);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void engine::camera::calculate_camera() {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
    {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, math::mat4::identity_mat().data);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, math::mat4::identity_mat().data);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void engine::camera::destroy_block() {
    glDeleteBuffers(1, &ubo_id);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void engine::camera::look_at(const math::vec3& eye, const math::vec3& center, const math::vec3& up) {
    this->eye = math:: vec3(eye);
    this->center = math::vec3(center);
    this->up = math::vec3(up);
}

void engine::camera::perspective(const float fov, const float aspect, const float near, const float far) {
    const float pi = std::acos(-1);

    float rad = fov * pi / 180.0f;
    rad /= 2;
    float d = 1 / std::tan(rad);

    project_mat = math::mat4(d / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, d, 0.0f, 0.0f,
        0.0f, 0.0f, (near + far) / (near - far), -1.0f,
        0.0f, 0.0f, 2 * far * near / (near - far), 0.0f);
}

void engine::camera::orthographic(const float left, const float right, const float up, const float bottom,
    const float near, const float far) {
    
    project_mat = math::mat4(2.0f / (right - left), 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f / (up - bottom), 0.0f, 0.0f,
        0.0f, 0.0f, 2.0f / (far - near), 0.0f,
        (left + right) / (left - right), (up + bottom) / (up - bottom),
        (near + far) / (near - far), 1.0f);
}

const engine::math::mat4 engine::camera::view() const {
    math::vec3 v = (center - eye).normalized();
    math::vec3 s = cross(v, up).normalized();
    math::vec3 u = cross(s, v);

    return math::mat4(s.x, u.x, -v.x, 0.0f,
        s.y, u.y, -v.y, 0.0f,
        s.z, u.z, -v.z, 0.0f,
        -dot(s, eye), -dot(u, eye), dot(v, eye), 1.0f);
}

const engine::math::mat4 engine::camera::projection() const {
    return project_mat;
}
