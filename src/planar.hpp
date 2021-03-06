#pragma once

#include "engine/i_app.hpp"

struct planar : engine::i_app {
	engine::math::vec3 light_pos = engine::math::vec3(0.0f, 5.0f, 10.0f);

	virtual void window_close_callback(GLFWwindow* win) override;
	virtual void window_size_callback(GLFWwindow* win, int winx, int winy) override;
	virtual void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) override;
	virtual void mouse_callback(GLFWwindow* win, double xpos, double ypos) override;
	virtual void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) override;
	virtual void setup(int winx, int winy) override;
	virtual void display(float elapsed_sec) override;

	void setup_shaders();
};