#include <array>

#include "scene.hpp"

#include "shader.hpp"
#include "manager/shader_manager.hpp"
#include "manager/mesh_manager.hpp"

std::shared_ptr<engine::scene> engine::scene::instance;

void engine::scene::create_objects() {
    engine::math::vec4 purple(163.0f / 255.0f, 92.0f / 255.0f, 189.0f / 255.0f, 1.0f);
    engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);
    engine::math::vec4 red(223.0f / 255.0f, 86.0f / 255.0f, 86.0f / 255.0f, 1.0f);
    engine::math::vec4 blue(86.0f / 255.0f, 116.0f / 255.0f, 223.0f / 255.0f, 1.0f);
    engine::math::vec4 green(62.0f / 255.0f, 137.0f / 255.0f, 98.0f / 255.0f, 1.0f);
    engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);
    engine::math::vec4 teal(19.0f / 255.0f, 111.0f / 255.0f, 114.0f / 255.0f, 1.0f);
    math::vec3 z_axis(0.0f, 0.0f, 1.0f);

    std::shared_ptr<shader> shdr = manager::shader_manager::get_instance()->elements["main"];
    std::shared_ptr<geometry::object> ground = std::make_shared<geometry::object>();
    ground->shdr = shdr;

    math::mat4 transform = math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    std::shared_ptr<geometry::object> obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["square"];
    obj->transform = transform;
    obj->color = purple;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rsquare"];
    obj->transform = transform;
    obj->color = math::vec4(purple.x * 0.5f, purple.y * 0.5f, purple.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
        math::mat_fact::rodr_rot(45.0f, z_axis); 
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["triangle"];
    obj->transform = transform;
    obj->color = yellow;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rtriangle"];
    obj->transform = transform;
    obj->color = math::vec4(yellow.x * 0.5f, yellow.y * 0.5f, yellow.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
        math::mat_fact::rodr_rot(135.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["triangle"];
    obj->transform = transform;
    obj->color = red;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rtriangle"];
    obj->transform = transform;
    obj->color = math::vec4(red.x * 0.5f, red.y * 0.5f, red.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
        math::mat_fact::rodr_rot(180.0f, z_axis) *
        math::mat_fact::scale(0.71f, 0.71f, 1.0f);
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["triangle"];
    obj->transform = transform;
    obj->color = blue;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rtriangle"];
    obj->transform = transform;
    obj->color = math::vec4(blue.x * 0.5f, blue.y * 0.5f, blue.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis);
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["triangle"];
    obj->transform = transform;
    obj->color = green;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rtriangle"];
    obj->transform = transform;
    obj->color = math::vec4(green.x * 0.5f, green.y * 0.5f, green.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
        math::mat_fact::scale(0.95f, 0.243f, 1.0f);
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["para"];
    obj->transform = transform;
    obj->color = brown;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rpara"];
    obj->transform = transform;
    obj->color = math::vec4(brown.x * 0.5f, brown.y * 0.5f, brown.z * 0.5f, 1.0f);

    transform =
        math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
        math::mat_fact::rodr_rot(225.0f, z_axis) *
        math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["triangle"];
    obj->transform = transform;
    obj->color = teal;
    obj = ground->create_node();
    obj->m = manager::mesh_manager::get_instance()->elements["rtriangle"];
    obj->transform = transform;
    obj->color = math::vec4(teal.x * 0.5f, teal.y * 0.5f, teal.z * 0.5f, 1.0f);

    for(auto o : ground->children) {
        o->transform = o->transform *
            engine::math::mat_fact::scale(0.75, 0.75, 1.0f);
    }

    objs.push_back(ground);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void engine::scene::draw() {
    for(auto& o : objs) {
        o->draw();
    }
    glUseProgram(0);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}
