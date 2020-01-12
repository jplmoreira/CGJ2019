#pragma once

#include "../i_app.hpp"

struct sepia : engine::i_app {
	unsigned int SCR_WIDTH = 0;
	unsigned int SCR_HEIGHT = 0;

	GLuint sepia_fbo;
	GLuint color_buffer;

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
