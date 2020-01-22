#include "wood.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void wood::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void wood::window_size_callback(GLFWwindow* win, int winx, int winy) {
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void wood::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {}

void wood::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void wood::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	} else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void wood::setup_shaders() {
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();
	main->compile("res/shaders/wood_vs.glsl", "res/shaders/wood_fs.glsl");                  //shader normal com matrizes pvm, mt basico
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");
	main->uniforms["in_color"] = glGetUniformLocation(main->get_id(), "in_color");
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);
	main->cleanup();
	engine::manager::shader_manager::get_instance()->elements["main"] = main;
}

void wood::setup(int winx, int winy) {
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(1.0f, 0.0f, 0.0f));

	setup_shaders();

	engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);  //criamos cor castanha para interpolacao

	engine::manager::mesh_manager::get_instance()->elements["quad"] =
		std::make_shared<engine::geometry::mesh>("res/models/quad.obj");   //vamos buscar a mesh do quad 

	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];   //criamos a cena 

	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();    //criamos o objecto
	obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];                        //Adicionamos mesh do quad ao obj
	obj->transform = engine::math::mat4::identity_mat();										     //nao alteramos o quad
	obj->color = brown;																				 //passamos o castanho uniform var para o fragment
	main_scene->root_obj->add_node(obj);															 //Adicionamos o no do obj ao root node

	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;                   //guardamos cena no scene mnger
}

void wood::display(float elapsed_sec) {
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);

	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
}