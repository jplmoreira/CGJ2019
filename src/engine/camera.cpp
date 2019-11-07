#include <cmath>
#include <chrono>

#include "camera.hpp"
#include "shader.hpp"

std::shared_ptr<engine::camera> engine::camera::instance;

engine::camera::camera() :
    ubo_id(0), fov(0), near(0), far(0), ortho(false) {}

void engine::camera::create_block() {
    glGenBuffers(1, &ubo_id);

    glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
    {
        glBufferData(GL_UNIFORM_BUFFER, sizeof(float) * 16 * 2, 0, GL_STREAM_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, shader::get_instance()->get_block_ptr(), ubo_id);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void engine::camera::calculate_camera(double time_elapsed) {
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_id);
    {
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float) * 16, view().data);
        glBufferSubData(GL_UNIFORM_BUFFER, sizeof(float) * 16, sizeof(float) * 16, projection().data);
    }
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    eye += dir * velocity * time_elapsed;
    center += dir * velocity * time_elapsed;
}

void engine::camera::destroy_block() {
    glDeleteBuffers(1, &ubo_id);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void engine::camera::setup(const bool ortho, const int w, const int h, const float fov, const float near, const float far) {
    this->ortho = ortho;
    this->fov = fov;
    this->near = near;
    this->far = far;
    resize(w, h);
}

void engine::camera::resize(const int w, const int h) {
    if(ortho) {
        float o_w;
        float o_h;
        if(w > h) {
            o_h = 1.0f;
            o_w = (float)w / h;
        } else {
            o_w = 1.0f;
            o_h = (float)h / w;
        }
        orthographic(-o_w, o_w, o_h, -o_h, this->near, this->far);
    } else {
        float aspect = (float)w / h;
        perspective(this->fov, aspect, this->near, this->far);
    }
}

void engine::camera::make_ortho(const bool ortho) {
    this->ortho = ortho;
}

void engine::camera::field_of_view(const float fov) {
    this->fov = fov;
}

void engine::camera::view_planes(const float near, const float far) {
    this->near = near;
    this->far = far;
}

void engine::camera::look_at(const math::vec3& eye, const math::vec3& center, const math::vec3& up) {
    this->eye = math:: vec3(eye);
    this->center = math::vec3(center);
    this->up = math::vec3(up);
}

void engine::camera::move(DIR direction) {
    if(direction == DIR::RIGHT) {
        dir = cross((center - eye).normalized(), up).normalized();
    } else if(direction == DIR::LEFT) {
        dir = -cross((center - eye).normalized(), up).normalized();
    } else if(direction == DIR::UP) {
        dir = (center - eye).normalized();
    } else if(direction == DIR::DOWN) {
        dir = (eye - center).normalized();
    } else if(direction == DIR::STOP) {
        dir = math::vec3();
    }
}

void engine::camera::activate_rotation(bool activate) {
    rotation = activate;
    if(!activate) last_pos = math::vec2(-1.0f, -1.0f);
}

void engine::camera::rotate(float x, float y) {
    if(rotation) {
        if(last_pos.x < 0.0f || last_pos.y < 0.0f) {
            last_pos = math::vec2(x, y);
        } else {
            math::vec2 diff = math::vec2(x, y) - last_pos;
            if(std::fabs(diff.x) < std::fabs(diff.y)) {   // PITCH
                math::vec3 v = center - eye;
                math::vec3 s = cross(v, up).normalized();

                float angle = 0.001f;
                math::mat3 rot_mat = math::mat_fact::rodr_rot(angle * diff.y, s);
                math::vec3 v_rot = rot_mat * v;
                center = eye + v_rot;
                up = rot_mat * up;
            } else {                                    // YAW
                math::vec3 v = center - eye;
                math::vec3 s = cross(v, up).normalized();
                math::vec3 u = cross(s, v);

                float angle = 0.01f;
                math::vec3 v_rot = math::mat_fact::rodr_rot(angle * diff.x, u) * v;
                center = eye + v_rot;
                last_pos = math::vec2(x, y);
            }
        }
    }
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
        0.0f, 0.0f, 2.0f / (near - far), 0.0f,
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
