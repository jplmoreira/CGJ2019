#include "scene.hpp"

#include "geometry/geometry.hpp"
#include "shader.hpp"

std::shared_ptr<engine::scene> engine::scene::instance;

void engine::scene::create_objects() {
    math::vec3 z_axis(0.0f, 0.0f, 1.0f);

    geometry::object obj = geometry::create_object(v_square, i_square, purple);
    obj.transform =
        math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    obj = geometry::create_object(v_triangle, i_triangle, yellow);
    obj.transform =
        math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis);
    objs.push_back(obj);

    obj = geometry::create_object(v_triangle, i_triangle, red);
    obj.transform =
        math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
        math::mat_fact::rodr_rot(135.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    obj = geometry::create_object(v_triangle, i_triangle, blue);
    obj.transform =
        math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
        math::mat_fact::rodr_rot(180.0f, z_axis) *
        math::mat_fact::scale(0.71f, 0.71f, 1.0f);
    objs.push_back(obj);

    obj = geometry::create_object(v_triangle, i_triangle, green);
    obj.transform =
        math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis);
    objs.push_back(obj);

    obj = geometry::create_object(v_para, i_para, brown);
    obj.transform =
        math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
        math::mat_fact::scale(0.95f, 0.243f, 1.0f);
    objs.push_back(obj);

    obj = geometry::create_object(v_triangle, i_triangle, teal);
    obj.transform =
        math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    for(auto& o : objs) {
        o.transform = o.transform *
            engine::math::mat_fact::scale(0.75, 0.75, 1.0f);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void engine::scene::delete_objects() {
    GLuint vbo[3];

    for(auto& o : objs) {
        glBindVertexArray(o.vao);
        glDisableVertexAttribArray(ATTR::VERTICES);
        glDisableVertexAttribArray(ATTR::COLORS);
        glDeleteBuffers(3, vbo);
        glDeleteVertexArrays(1, &o.vao);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
#endif
}

void engine::scene::draw() {
    for(auto& o : objs) {
        glBindVertexArray(o.vao);
        glUseProgram(shader::get_instance()->get_id());

        glUniformMatrix4fv(shader::get_instance()->get_uniform(), 1, GL_FALSE, o.transform.data);
        glDrawElements(GL_TRIANGLES, o.num_indexes, GL_UNSIGNED_SHORT, (GLvoid*)0);

        glUseProgram(0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}
