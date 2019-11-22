#include "object.hpp"

engine::geometry::object::object() :
    transform(1.0f), quaternion(1.0f, math::vec3()),
    color(1.0f) {}

std::shared_ptr<engine::geometry::object> engine::geometry::object::create_node() {
    std::shared_ptr<object> child = std::make_shared<object>();
    child->parent = shared_from_this();
    child->shdr = shdr;
    children.push_back(child);
    return children.back();
}

void engine::geometry::object::draw() {
    if(m) {
        shdr->enable();

        glUniformMatrix4fv(shdr->uniforms["ModelMatrix"], 1, GL_FALSE, transform.data);
        glUniform4fv(shdr->uniforms["in_color"], 1, color.data());

        m->draw();
    }
    for(auto child : children)
        child->draw();
}
