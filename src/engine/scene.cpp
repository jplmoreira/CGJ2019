#include "scene.hpp"

#include <GL/glew.h>

void engine::scene::prepare() {
    objects::object o = objects::create_triangle(engine::math::vec4(0.404f, 0.612f, 0.302f, 1.0f));
    o.trasform = math::mat4::identity_mat();
    objs.push_back(o);
}

void engine::scene::draw(unsigned int program_id, unsigned int transform_id) {
    for(objects::object& obj : objs) {
        glBindVertexArray(obj.vao);
        glUseProgram(program_id);

        glUniformMatrix4fv(transform_id, 1, GL_TRUE, obj.trasform.data);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*)0);

        glUseProgram(0);
        glBindVertexArray(0);
    }
}

void engine::scene::destroy() {
    unsigned int vbo[3];
    for(objects::object& obj : objs) {
        glBindVertexArray(obj.vao);
        glDisableVertexAttribArray(ATTR::VERTICES);
        glDisableVertexAttribArray(ATTR::COLORS);
        glDeleteBuffers(3, vbo);
        glDeleteVertexArrays(1, &obj.vao);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}
