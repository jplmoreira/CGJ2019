#include "rainy.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void rainy::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void rainy::window_size_callback(GLFWwindow* win, int winx, int winy) {
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void rainy::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {}

void rainy::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	//engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void rainy::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	//if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
	//	engine::camera::get_instance()->activate_rotation(true);
	//} else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
	//	engine::camera::get_instance()->activate_rotation(false);
	//}
}

void rainy::setup(int winx, int winy) {
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 2.5f, -15.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));

	setup_shaders();

	engine::manager::mesh_manager::get_instance()->elements["quad"] =
		std::make_shared<engine::geometry::mesh>("res/models/quad.obj");
	engine::manager::mesh_manager::get_instance()->elements["table"] =
		std::make_shared<engine::geometry::mesh>("res/models/scene/table_sq.obj");

	engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);
	engine::math::vec4 gray(180.0f / 255.0f, 180.0f / 255.0f, 180.0f / 255.0f, 1.0f);
	engine::math::vec4 blue(0.0f / 255.0f, 2.0f / 255.0f, 118.0f / 255.0f, 1.0f);

	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];

	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["table"];
	obj->transform = engine::math::mat4::identity_mat();
	obj->color = brown;
	main_scene->root_obj->add_node(obj);

	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	obj->transform = engine::math::mat_fact::translate(0.0f, 0.0f, 3.76f) *
		engine::math::mat_fact::rodr_rot(180.0f, engine::math::vec3(0.0f, 1.0f, 0.0f)) *
		engine::math::mat_fact::scale(100.0f, 100.0f, 0.0f);
	obj->color = gray;
	main_scene->root_obj->add_node(obj);

	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;
}

void rainy::display(float elapsed_sec) {
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);

	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
}

void rainy::setup_shaders() {
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();
	main->compile("res/shaders/rainy_vs.glsl", "res/shaders/rainy_fs.glsl");
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");
	main->uniforms["in_color"] = glGetUniformLocation(main->get_id(), "in_color");
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);
	main->cleanup();
	engine::manager::shader_manager::get_instance()->elements["main"] = main;
}