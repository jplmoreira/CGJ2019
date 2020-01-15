#include "planar.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void planar::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void planar::window_size_callback(GLFWwindow* win, int winx, int winy) {
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void planar::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {}

void planar::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void planar::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	} else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void planar::setup_shaders() {
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();
	main->compile("res/shaders/planar_vert.glsl", "res/shaders/planar_frag.glsl");
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");
	main->uniforms["in_color"] = glGetUniformLocation(main->get_id(), "in_color");
	main->uniforms["light_pos"] = glGetUniformLocation(main->get_id(), "light_pos");
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);
	main->cleanup();
	engine::manager::shader_manager::get_instance()->elements["main"] = main;

	std::shared_ptr<engine::shader> shadow = std::make_shared<engine::shader>();
	shadow->compile("res/shaders/shadow_vert.glsl", "res/shaders/shadow_frag.glsl");
	shadow->uniforms["ModelMatrix"] = glGetUniformLocation(shadow->get_id(), "ModelMatrix");
	shadow->uniforms["ShadowProjMat"] = glGetUniformLocation(shadow->get_id(), "ShadowProjMat");
	ubo_id = glGetUniformBlockIndex(shadow->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(shadow->get_id(), ubo_id, shadow->blocks["SharedMatrices"]);
	shadow->cleanup();
	engine::manager::shader_manager::get_instance()->elements["shadow"] = shadow;
}

void planar::setup(int winx, int winy) {
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 10.0f, 10.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));

	setup_shaders();

	engine::manager::mesh_manager::get_instance()->elements["cube"] =
		std::make_shared<engine::geometry::mesh>("res/models/cube.obj");
	engine::manager::mesh_manager::get_instance()->elements["quad"] =
		std::make_shared<engine::geometry::mesh>("res/models/quad.obj");

	engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);
	engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);

	engine::math::mat4 transform1 = engine::math::mat_fact::scale(0.25f, 0.25f, 0.25f) *
		engine::math::mat_fact::translate(0.0f, 1.0f, 0.0f);

	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];

	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	obj->transform = transform1;
	obj->color = yellow;
	main_scene->root_obj->add_node(obj);

	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;

	std::shared_ptr<engine::scene> shadow_scene = std::make_shared<engine::scene>();
	shadow_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["shadow"];

	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	obj->transform = transform1;
	shadow_scene->root_obj->add_node(obj);

	engine::manager::scene_manager::get_instance()->elements["shadow"] = shadow_scene;

	std::shared_ptr<engine::scene> plane_scene = std::make_shared<engine::scene>();
	plane_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];
	obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	obj->transform = engine::math::mat_fact::translate(0.0f, -0.001f, 0.0f)
		* engine::math::mat4(engine::math::mat_fact::rodr_rot(-90.0f, engine::math::vec3(1.0f, 0.0f, 0.0f)));
	obj->color = brown;
	plane_scene->root_obj->add_node(obj);

	engine::manager::scene_manager::get_instance()->elements["plane"] = plane_scene;
}

void planar::display(float elapsed_sec) {
	engine::math::vec3 light_pos(5.0f);
	engine::math::vec3 p_point(0.0f);
	engine::math::vec3 p_normal(0.0f, 1.0f, 0.0f);
	engine::math::mat4 shadow_mat =
		engine::math::mat_fact::shadow(light_pos, p_point, p_normal);

	std::shared_ptr<engine::shader> main =
		engine::manager::shader_manager::get_instance()->elements["main"];
	std::shared_ptr<engine::shader> shadow =
		engine::manager::shader_manager::get_instance()->elements["shadow"];
	main->enable();
	glUniform3fv(main->uniforms["light_pos"], 1, light_pos.data());
	main->disable();
	shadow->enable();
	glUniformMatrix4fv(shadow->uniforms["ShadowProjMat"], 1, GL_FALSE, shadow_mat.data);
	shadow->disable();

	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);

	engine::manager::scene_manager::get_instance()->elements["plane"]->draw();
	engine::manager::scene_manager::get_instance()->elements["shadow"]->draw();
	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
}
