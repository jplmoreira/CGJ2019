#pragma once

#include "engine/i_app.hpp"

struct bloom : engine::i_app {
	unsigned int SCR_WIDTH = 0;
	unsigned int SCR_HEIGHT = 0;

	GLuint bloom_fbo;
	GLuint color_buffers[2];
	GLuint pingpong_fbos[2];
	GLuint pingpong_color_buffers[2];

	virtual void window_close_callback(GLFWwindow* win) override;
	virtual void window_size_callback(GLFWwindow* win, int winx, int winy) override;
	virtual void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) override;
	virtual void mouse_callback(GLFWwindow* win, double xpos, double ypos) override;
	virtual void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) override;
	virtual void setup(int winx, int winy) override;
	virtual void display(float elapsed_sec) override;
	void setup_shaders();
	void create_fbos();
};