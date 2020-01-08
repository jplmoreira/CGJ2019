#include "object.hpp"

engine::geometry::object::object() :
    transform(1.0f), quaternion(1.0f, math::vec3()),
    color(1.0f) {}

engine::geometry::object::~object() {
    m.reset();
    shdr.reset();
    for(auto& child : children)
        child.reset();
    children.clear();
}

void engine::geometry::object::add_node(std::unique_ptr<engine::geometry::object>& obj) {
    obj->shdr = shdr;
    children.push_back(std::move(obj));
}

void engine::geometry::object::draw() {
    if(m) {
        shdr->enable();

        glUniformMatrix4fv(shdr->uniforms["ModelMatrix"], 1, GL_FALSE, transform.data);
        glUniform4fv(shdr->uniforms["in_color"], 1, color.data());

        int tex_unit = 0;
        for(auto& tex : textures) {
            glActiveTexture(GL_TEXTURE0 + tex_unit);
            glBindTexture(GL_TEXTURE_2D, tex->id);
            tex_unit++;
        }

        m->draw();
    }
    for(auto& child : children)
        child->draw();
}