#include <array>

#include "scene.hpp"

#include "shader.hpp"
#include "geometry/geometry.hpp"
#include "manager/shader_manager.hpp"

std::shared_ptr<engine::scene> engine::scene::instance;

void engine::scene::create_objects() {
    math::vec3 z_axis(0.0f, 0.0f, 1.0f);

    GLushort ri_triangle[3] = { i_triangle[2], i_triangle[1], i_triangle[0] };
    GLushort ri_square[6] = { i_square[5], i_square[4], i_square[3], i_square[2], i_square[1], i_square[0] };
    GLushort ri_para[6] = { i_para[5], i_para[4], i_para[3], i_para[2], i_para[1], i_para[0] };

    math::mat4 transform = math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    geometry::object obj = geometry::create_object(v_square, i_square, purple);
    obj.transform = transform;        
    objs.push_back(obj);
    obj = geometry::create_object(v_square, ri_square, math::vec4(purple.x * 0.5f, purple.y * 0.5f, purple.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis); 
    obj = geometry::create_object(v_triangle, i_triangle, yellow);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_triangle, ri_triangle, math::vec4(yellow.x * 0.5f, yellow.y * 0.5f, yellow.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
        math::mat_fact::rodr_rot(135.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    obj = geometry::create_object(v_triangle, i_triangle, red);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_triangle, ri_triangle, math::vec4(red.x * 0.5f, red.y * 0.5f, red.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
        math::mat_fact::rodr_rot(180.0f, z_axis) *
        math::mat_fact::scale(0.71f, 0.71f, 1.0f);
    obj = geometry::create_object(v_triangle, i_triangle, blue);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_triangle, ri_triangle, math::vec4(blue.x * 0.5f, blue.y * 0.5f, blue.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis);
    obj = geometry::create_object(v_triangle, i_triangle, green);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_triangle, ri_triangle, math::vec4(green.x * 0.5f, green.y * 0.5f, green.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
        math::mat_fact::scale(0.95f, 0.243f, 1.0f);
    obj = geometry::create_object(v_para, i_para, brown);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_para, ri_para, math::vec4(brown.x * 0.5f, brown.y * 0.5f, brown.z * 0.5f, 1.0f));
    obj.transform = transform;
    objs.push_back(obj);

    transform =
        math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    obj = geometry::create_object(v_triangle, i_triangle, teal);
    obj.transform = transform;
    objs.push_back(obj);
    obj = geometry::create_object(v_triangle, ri_triangle, math::vec4(teal.x * 0.5f, teal.y * 0.5f, teal.z * 0.5f, 1.0f));
    obj.transform = transform;
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
    GLuint vbo[2];

    for(auto& o : objs) {
        glBindVertexArray(o.vao);
        glDisableVertexAttribArray(ATTR::VERTICES);
        glDeleteBuffers(2, vbo);
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
        shader shdr = manager::shader_manager::get_instance()->elements["main"];
        shdr.enable();

        glUniformMatrix4fv(shdr.uniforms["ModelMatrix"], 1, GL_FALSE, o.transform.data);
        glUniform4fv(shdr.uniforms["in_color"], 1, o.color.data());
        glDrawElements(GL_TRIANGLES, o.num_indexes, GL_UNSIGNED_SHORT, (GLvoid*)0);

        glUseProgram(0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}
