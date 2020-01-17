#define _CRT_SECURE_NO_WARNINGS
#include "window.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/geometry/mesh.hpp"
#include "engine/manager/mesh_manager.hpp"
#include "engine/manager/scene_manager.hpp"
#include "engine/manager/shader_manager.hpp"

#include <algorithm>
#include <time.h>

void window::window_close_callback(GLFWwindow* win) {
	engine::manager::scene_manager::free_instance();
	engine::manager::mesh_manager::free_instance();
	engine::manager::shader_manager::free_instance();
	engine::camera::get_instance()->destroy_block();
}

void window::window_size_callback(GLFWwindow* win, int winx, int winy) {
	engine::camera::get_instance()->resize(winx, winy);
	glViewport(0, 0, winx, winy);
}

void saveScreenshotToFile(std::string filename, int windowWidth, int windowHeight) {
	const int numberOfPixels = windowWidth * windowHeight * 3;
	unsigned char *pixels;
	pixels = (unsigned char*)malloc(numberOfPixels);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, windowWidth, windowHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);

	FILE* outputFile = fopen(filename.c_str(), "w");
	short header[] = { 0, 2, 0, 0, 0, 0, (short)windowWidth, (short)windowHeight, 24 };

	if (outputFile != NULL) {
		fwrite(&header, sizeof(header), 1, outputFile);
		fwrite(pixels, numberOfPixels, 1, outputFile);
		fclose(outputFile);
	}
	else
		std::cout << "Unable to create Screenshot.\n";

	std::cout << "Finished writing to file.\n";
}

void window::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(win, GLFW_TRUE);
		window_close_callback(win);
	} else if(key == GLFW_KEY_X && action == GLFW_PRESS) {
		int width, height;
		glfwGetWindowSize(win, &width, &height);

		time_t rawtime;
		struct tm* timeinfo;

		time(&rawtime);
		timeinfo = localtime(&rawtime);
		std::string time = asctime(timeinfo);
		time = time.c_str();
		size_t f1 = time.find(' ');
		size_t f2 = time.find('\n');
		time = time.substr(f1+1, 20);
		time.erase(std::remove(time.begin(), time.end(), ':'), time.end());

		std::string filename = "ss/awesomeSS";
		filename.append(time);
		filename.append(".tga");
		saveScreenshotToFile(filename, width, height);
	}
}

void window::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
	engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void window::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		engine::camera::get_instance()->activate_rotation(true);
	}
	else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
		engine::camera::get_instance()->activate_rotation(false);
	}
}

std::map<float, unsigned int> sort_draw_order(std::vector<engine::math::vec3> positions) {
	std::map<float, unsigned int> sorted;
	for (unsigned int i = 0; i < positions.size(); i++) {
		engine::math::vec3 distance = engine::camera::get_instance()->get_position() - positions[i];
		sorted[distance.quadrance()*1000+i] = i;
	}
	return sorted;
}

void window::setup(int winx, int winy) {
	engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
	engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
		engine::math::vec3(0.0f, 0.0f, 0.0f),
		engine::math::vec3(0.0f, 1.0f, 0.0f));

	engine::manager::shader_manager::get_instance()->elements["main"] =
		std::make_shared<engine::shader>("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
	// is this setting shaders for all the scene?
	// can we set a different shader for a particular object?

	engine::manager::mesh_manager::get_instance()->elements["cube"] =
		std::make_shared<engine::geometry::mesh>("res/models/cube.obj");

	engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);

	std::shared_ptr<engine::scene> main_scene = std::make_shared<engine::scene>();
	main_scene->root_obj->shdr = engine::manager::shader_manager::get_instance()->elements["main"];

	std::unique_ptr<engine::geometry::object> floor_right = std::make_unique<engine::geometry::object>();
	floor_right->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	floor_right->position = engine::math::vec3(0.5f, -1.0f, 0.0f);
	floor_right->transform = engine::math::mat_fact::translate(0.5f, -1.0f, 0.0f) * engine::math::mat_fact::scale(0.5f, 0.1f, 1.0f);
	floor_right->color = yellow;
	positions.push_back(floor_right->position);
	

	engine::math::vec4 cyan(0.0f / 255.0f, 240.0f / 255.0f, 240.0f / 255.0f, 1.0f);

	std::unique_ptr<engine::geometry::object> floor_left = std::make_unique<engine::geometry::object>();
	floor_left->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	floor_left->position = engine::math::vec3(-0.5f, -1.0f, 0.0f);
	floor_left->transform = engine::math::mat_fact::translate(-0.5f, -1.0f, 0.0f) * engine::math::mat_fact::scale(0.5f, 0.1f, 1.0f);
	floor_left->color = cyan;
	positions.push_back(floor_left->position);

	engine::math::vec4 white(240.0f / 255.0f, 240.0f / 255.0f, 240.0f / 255.0f, 0.3f);

	std::unique_ptr<engine::geometry::object> glass = std::make_unique<engine::geometry::object>();
	glass->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	glass->position = engine::math::vec3(0.0f, 0.0f, 0.0f);
	glass->transform = engine::math::mat_fact::scale(0.1f, 0.1f, 0.1f);
	glass->color = white;
	positions.push_back(glass->position);

	std::unique_ptr<engine::geometry::object> glass2 = std::make_unique<engine::geometry::object>();
	glass2->m = engine::manager::mesh_manager::get_instance()->elements["cube"];
	glass2->position = engine::math::vec3(0.0f, -0.5f, 0.0f);
	glass2->transform = engine::math::mat_fact::translate(0.0f, -0.5f, 0.0f) * engine::math::mat_fact::scale(0.05f, 0.05f, 0.05f);
	glass2->color = white;
	positions.push_back(glass2->position);
	
	std::map<float, unsigned int> depth = sort_draw_order(positions);

	for (std::map<float, unsigned int>::reverse_iterator it = depth.rbegin(); it != depth.rend(); ++it) {
		switch (it->second) {
		case 0:
			//main_scene->root_obj->add_node(floor_right);
			break;
		case 1:
			main_scene->root_obj->add_node(floor_left);
			break;
		case 2:
			main_scene->root_obj->add_node(glass);
			break;
		case 3:
			main_scene->root_obj->add_node(glass2);
			break;
		default:
			break;
		}
	}

	engine::manager::scene_manager::get_instance()->elements["main"] = main_scene;
}

bool compareInterval(std::unique_ptr<engine::geometry::object>& i1, std::unique_ptr<engine::geometry::object>& i2) {
	engine::math::vec3 distance1 = engine::camera::get_instance()->get_position() - i1->position;
	engine::math::vec3 distance2 = engine::camera::get_instance()->get_position() - i2->position;
	return (distance1.quadrance() > distance2.quadrance());
}

void window::display(float elapsed_sec) {
	engine::camera::get_instance()->calculate_camera((float)elapsed_sec);
	std::shared_ptr<engine::scene> main_scene = engine::manager::scene_manager::get_instance()->elements["main"];
	std::sort(main_scene->root_obj->children.begin(), main_scene->root_obj->children.end(), compareInterval);
	main_scene->draw();
}
