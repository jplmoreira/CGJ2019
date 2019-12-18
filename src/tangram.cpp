#include "tangram.hpp"

#include "engine/scene.hpp"
#include "engine/camera.hpp"
#include "engine/geometry/geometry.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void setup_shaders() {
	engine::manager::shader_manager::get_instance()->elements["main"] =
		std::make_shared<engine::shader>("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
}

void setup_meshes() {
	GLushort ri_triangle[3] = { i_triangle[2], i_triangle[1], i_triangle[0] };
	GLushort ri_square[6] = { i_square[5], i_square[4], i_square[3], i_square[2], i_square[1], i_square[0] };
	GLushort ri_para[6] = { i_para[5], i_para[4], i_para[3], i_para[2], i_para[1], i_para[0] };

	engine::manager::mesh_manager::get_instance()->elements["triangle"] =
		std::make_shared<engine::geometry::mesh>(v_triangle, i_triangle);
	engine::manager::mesh_manager::get_instance()->elements["rtriangle"] =
		std::make_shared<engine::geometry::mesh>(v_triangle, ri_triangle);
	engine::manager::mesh_manager::get_instance()->elements["square"] =
		std::make_shared<engine::geometry::mesh>(v_square, i_square);
	engine::manager::mesh_manager::get_instance()->elements["rsquare"] =
		std::make_shared<engine::geometry::mesh>(v_square, ri_square);
	engine::manager::mesh_manager::get_instance()->elements["para"] =
		std::make_shared<engine::geometry::mesh>(v_para, i_para);
	engine::manager::mesh_manager::get_instance()->elements["rpara"] =
		std::make_shared<engine::geometry::mesh>(v_para, ri_para);
}

void setup_scenes() {
	engine::math::vec4 purple(163.0f / 255.0f, 92.0f / 255.0f, 189.0f / 255.0f, 1.0f);
	engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);
	engine::math::vec4 red(223.0f / 255.0f, 86.0f / 255.0f, 86.0f / 255.0f, 1.0f);
	engine::math::vec4 blue(86.0f / 255.0f, 116.0f / 255.0f, 223.0f / 255.0f, 1.0f);
	engine::math::vec4 green(62.0f / 255.0f, 137.0f / 255.0f, 98.0f / 255.0f, 1.0f);
	engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);
	engine::math::vec4 teal(19.0f / 255.0f, 111.0f / 255.0f, 114.0f / 255.0f, 1.0f);
	engine::math::vec3 z_axis(0.0f, 0.0f, 1.0f);

	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];

	engine::math::mat4 transform = engine::math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
		engine::math::mat_fact::rodr_rot(45.0f, z_axis) *
		engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["square"];
	obj->transform = transform;
	obj->color = purple;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rsquare"];
	obj->transform = transform;
	obj->color = engine::math::vec4(purple.x * 0.5f, purple.y * 0.5f, purple.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
		engine::math::mat_fact::rodr_rot(45.0f, z_axis);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["triangle"];
	obj->transform = transform;
	obj->color = yellow;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rtriangle"];
	obj->transform = transform;
	obj->color = engine::math::vec4(yellow.x * 0.5f, yellow.y * 0.5f, yellow.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
		engine::math::mat_fact::rodr_rot(135.0f, z_axis) *
		engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["triangle"];
	obj->transform = transform;
	obj->color = red;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rtriangle"];
	obj->transform = transform;
	obj->color = engine::math::vec4(red.x * 0.5f, red.y * 0.5f, red.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
		engine::math::mat_fact::rodr_rot(180.0f, z_axis) *
		engine::math::mat_fact::scale(0.71f, 0.71f, 1.0f);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["triangle"];
	obj->transform = transform;
	obj->color = blue;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rtriangle"];
	obj->transform = transform;
	obj->color = engine::math::vec4(blue.x * 0.5f, blue.y * 0.5f, blue.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
		engine::math::mat_fact::rodr_rot(225.0f, z_axis);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["triangle"];
	obj->transform = transform;
	obj->color = green;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rtriangle"];
	obj->transform = transform;
	obj->color = engine::math::vec4(green.x * 0.5f, green.y * 0.5f, green.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
		engine::math::mat_fact::scale(0.95f, 0.243f, 1.0f);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["para"];
	obj->transform = transform;
	obj->color = brown;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rpara"];
	obj->transform = transform;
	obj->color = engine::math::vec4(brown.x * 0.5f, brown.y * 0.5f, brown.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	transform =
		engine::math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
		engine::math::mat_fact::rodr_rot(225.0f, z_axis) *
		engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["triangle"];
	obj->transform = transform;
	obj->color = teal;
	main_scene->root_obj->add_node(obj);
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["rtriangle"];
	obj->transform = transform;
	obj->color = engine::math::vec4(teal.x * 0.5f, teal.y * 0.5f, teal.z * 0.5f, 1.0f);
	main_scene->root_obj->add_node(obj);

	for(auto& o : main_scene->root_obj->children) {
		o->transform = o->transform *
			engine::math::mat_fact::scale(0.75, 0.75, 1.0f);
	}

	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;

#ifndef ERROR_CALLBACK
	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void tangram::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void tangram::window_size_callback(GLFWwindow* win, int winx, int winy) {
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void tangram::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		window_close_callback(win);
	} else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
		engine::camera::get_instance()->move(engine::camera::DIR::UP);
	} else if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
		engine::camera::get_instance()->move(engine::camera::DIR::STOP);
	} else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
		engine::camera::get_instance()->move(engine::camera::DIR::DOWN);
	} else if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
		engine::camera::get_instance()->move(engine::camera::DIR::STOP);
	} else if(key == GLFW_KEY_D && action == GLFW_PRESS) {
		engine::camera::get_instance()->move(engine::camera::DIR::RIGHT);
	} else if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
		engine::camera::get_instance()->move(engine::camera::DIR::STOP);
	} else if(key == GLFW_KEY_A && action == GLFW_PRESS) {
		engine::camera::get_instance()->move(engine::camera::DIR::LEFT);
	} else if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
		engine::camera::get_instance()->move(engine::camera::DIR::STOP);
	} else if(key == GLFW_KEY_P && action == GLFW_PRESS) {
		engine::camera::get_instance()->change_project(true);
	} else if(key == GLFW_KEY_P && action == GLFW_RELEASE) {
		engine::camera::get_instance()->change_project(false);
	} else if(key == GLFW_KEY_G && action == GLFW_PRESS) {
		engine::camera::get_instance()->toggle_gimbal();
	}
}

void tangram::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void tangram::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	} else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void tangram::setup(int winx, int winy) {
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));
	setup_shaders();
	setup_meshes();
	setup_scenes();
}

void tangram::display(float elapsed_sec) {
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);
	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
}