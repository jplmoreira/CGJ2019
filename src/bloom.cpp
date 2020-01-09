#include "bloom.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

void bloom::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void bloom::window_size_callback(GLFWwindow* win, int winx, int winy) {
	SCR_WIDTH = winx;
	SCR_HEIGHT = winy;
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void bloom::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {}

void bloom::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void bloom::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

void bloom::setup(int winx, int winy) {
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

	engine::math::vec4 glow_color(1.0f, 1.0f, 1.0f, 1.0f);

	//main scene
	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];
	std::unique_ptr<engine::geometry::object> obj = std::make_unique<engine::geometry::object>();
	obj->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	obj->transform = engine::math::mat_fact::scale(0.4f, 0.4f, 0.4f);
	obj->color = glow_color;
	main_scene->root_obj->add_node(obj);
	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;

	//blur scene
	std::shared_ptr<engine::scene> blur_scene = std::make_shared<engine::scene>();
	blur_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["blur"];
	std::unique_ptr<engine::geometry::object> quad_obj = std::make_unique<engine::geometry::object>();
	quad_obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	blur_scene->root_obj->add_node(quad_obj);
	engine::manager::scene_manager::get_instance()->elements["blur"] = blur_scene;

	//bloom scene
	std::shared_ptr<engine::scene> bloom_scene = std::make_shared<engine::scene>();
	bloom_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["bloom"];
	quad_obj = std::make_unique<engine::geometry::object>();
	quad_obj->m = engine::manager::mesh_manager::get_instance()->elements["quad"];
	std::shared_ptr<engine::texture> scene = std::make_shared<engine::texture>(color_buffers[0]);
	std::shared_ptr<engine::texture> bloom_blur = std::make_shared<engine::texture>(pingpong_color_buffers[0]);
	quad_obj->textures.push_back(scene);
	quad_obj->textures.push_back(bloom_blur);
	bloom_scene->root_obj->add_node(quad_obj);
	engine::manager::scene_manager::get_instance()->elements["bloom"] = bloom_scene;
}

void bloom::display(float elapsed_sec) {
	//main
	glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);
	engine::manager::scene_manager::get_instance()->elements["main"]->draw();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//blur
	bool horizontal = true;
	bool first_iteration = true;
	const int amount = 10;
	std::shared_ptr<engine::shader> blur_shdr = engine::manager::shader_manager::get_instance()->elements["blur"];
	for (int i = 0; i < amount; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, pingpong_fbos[horizontal]);
		blur_shdr->enable();
		glUniform1i(blur_shdr->uniforms["horizontal"], horizontal);
		glBindTexture(GL_TEXTURE_2D, first_iteration ? color_buffers[1] : pingpong_color_buffers[!horizontal]);
		blur_shdr->disable();
		engine::manager::scene_manager::get_instance()->elements["blur"]->draw();
		horizontal = !horizontal;
		if (first_iteration)
			first_iteration = false;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//bloom
	engine::manager::scene_manager::get_instance()->elements["bloom"]->draw();
}

void bloom::setup_shaders() {
	std::shared_ptr<engine::shader> main = std::make_shared<engine::shader>();
	main->compile("res/shaders/bright_vert.glsl", "res/shaders/bright_frag.glsl");
	main->uniforms["ModelMatrix"] = glGetUniformLocation(main->get_id(), "ModelMatrix");
	main->uniforms["in_color"] = glGetUniformLocation(main->get_id(), "in_color");
	GLint ubo_id = glGetUniformBlockIndex(main->get_id(), "SharedMatrices");
	main->blocks["SharedMatrices"] = 0;
	glUniformBlockBinding(main->get_id(), ubo_id, main->blocks["SharedMatrices"]);
	main->cleanup();
	engine::manager::shader_manager::get_instance()->elements["main"] = main;


	std::shared_ptr<engine::shader> blur = std::make_shared<engine::shader>();
	blur->compile("res/shaders/blur_vert.glsl", "res/shaders/blur_frag.glsl");
	blur->uniforms["horizontal"] = glGetUniformLocation(blur->get_id(), "horizontal");
	blur->cleanup();
	blur->enable();
	glUniform1i(glGetUniformLocation(blur->get_id(), "image"), 0);  //uniform texture initialization
	blur->disable();
	engine::manager::shader_manager::get_instance()->elements["blur"] = blur;


	std::shared_ptr<engine::shader> bloom = std::make_shared<engine::shader>();
	bloom->compile("res/shaders/bloom_vert.glsl", "res/shaders/bloom_frag.glsl");
	bloom->cleanup();
	bloom->enable();
	glUniform1i(glGetUniformLocation(blur->get_id(), "scene"), 0);  //uniform texture initialization
	glUniform1i(glGetUniformLocation(blur->get_id(), "bloom_blur"), 1);  //uniform texture initialization
	bloom->disable();
	engine::manager::shader_manager::get_instance()->elements["bloom"] = bloom;
}

void bloom::create_fbos() {
	//create bloom fbo
	glGenFramebuffers(1, &bloom_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, bloom_fbo);
	glGenTextures(2, color_buffers);

	for (int i = 0; i < 2; i++) {
		glBindTexture(GL_TEXTURE_2D, color_buffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, color_buffers[i], 0);
	}
	
	//create depth rbo
	GLuint rbo_depth;
	glGenRenderbuffers(1, &rbo_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo_depth);

	GLuint attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//create pingpongs
	glGenFramebuffers(2, pingpong_fbos);
	glGenTextures(2, pingpong_color_buffers);
	
	for (int i = 0; i < 2; i++) {
		glBindFramebuffer(GL_FRAMEBUFFER, pingpong_fbos[i]);
		glBindTexture(GL_TEXTURE_2D, pingpong_color_buffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpong_color_buffers[i], 0);
		//check if framebuffers are complete
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete." << std::endl;
	}
	
}