#include "sepia.hpp"

#include "../camera.hpp"
#include "../shader.hpp"
#include "../geometry/mesh.hpp"
#include "../manager/mesh_manager.hpp"
#include "../manager/scene_manager.hpp"
#include "../manager/shader_manager.hpp"

void sepia::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void sepia::window_size_callback(GLFWwindow* win, int winx, int winy) {
	SCR_WIDTH = winx;
	SCR_HEIGHT = winy;
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void sepia::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	if(key == GLFW_KEY_T && action == GLFW_PRESS) {
		toggle = !toggle;
	}
}

void sepia::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void sepia::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void sepia::setup(int winx, int winy) {
	SCR_WIDTH = winx;
	SCR_HEIGHT = winy;
	setup_shaders();
	create_fbos();
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));

	engine::manager::mesh_manager::get_instance()->elements["cube"] =
		std::make_shared<engine::geometry::mesh>("res/models/cube.obj");
	engine::manager::mesh_manager::get_instance()->elements["quad"] =
		std::make_shared<engine::geometry::mesh>("res/models/quad.obj");

	//main scene
	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];
	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	obj->transform = engine::math::mat_fact::scale(0.4f, 0.4f, 0.4f);
	std::shared_ptr<engine::texture> tex = std::make_shared<engine::texture>("res/models/cube_texture.png");
	obj->textures.push_back(tex);
	main_scene->root_obj->add_node(obj);
	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;

	//sepia scene
	std::shared_ptr<engine::scene> sepia_scene = std::make_shared<engine::scene>();
	sepia_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["sepia"];
	std::unique_ptr<engine::geometry::object> quad_obj = std::make_unique<engine::geometry::object>();
	quad_obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	std::shared_ptr<engine::texture> image = std::make_shared<engine::texture>(color_buffer);
	quad_obj->textures.push_back(image);
	sepia_scene->root_obj->add_node(quad_obj);
	engine::manager::scene_manager::get_instance()->elements["sepia"] = sepia_scene;
}

void sepia::display(float elapsed_sec) {
	//main
	glBindFramebuffer(GL_FRAMEBUFFER, sepia_fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);
	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//sepia
	std::shared_ptr<engine::shader> sepia = engine::manager::shader_manager::get_instance()->elements["sepia"];
	sepia->enable();
	glUniform1i(sepia->uniforms["toggle"], toggle);
	sepia->disable();

	engine::manager::scene_manager::get_instance()->elements["sepia"]->root_obj->children[0]->textures[0]->id = color_buffer;
	engine::manager::scene_manager::get_instance()->elements["sepia"]->draw();
}

void sepia::setup_shaders() {
	//main filter shaders
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();
	main->compile("res/shaders/filter_vert.glsl", "res/shaders/filter_frag.glsl");
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);
	main->cleanup();
	main->enable();
	glUniform1i(glGetUniformLocation(main->get_id(), "tex"), 0);  //uniform texture initialization
	main->disable();
	engine::manager::shader_manager::get_instance()->elements["main"] = main;

	//sepia shaders
	std::shared_ptr<engine::shader> sepia = std::make_shared<engine::shader>();
	sepia->compile("res/shaders/sepia_vert.glsl", "res/shaders/sepia_frag.glsl");
	sepia->uniforms["toggle"] = glGetUniformLocation(sepia->get_id(), "toggle");
	sepia->cleanup();
	sepia->enable();
	glUniform1i(glGetUniformLocation(sepia->get_id(), "image"), 0);  //uniform texture initialization
	sepia->disable();
	engine::manager::shader_manager::get_instance()->elements["sepia"] = sepia;
}

void sepia::create_fbos() {
	//create sepia fbo
	glGenFramebuffers(1, &sepia_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, sepia_fbo);
	glGenTextures(1, &color_buffer);
	glBindTexture(GL_TEXTURE_2D, color_buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_buffer, 0);

	//create depth rbo
	GLuint rbo_depth;
	glGenRenderbuffers(1, &rbo_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

	GLuint attachment = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &attachment);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}