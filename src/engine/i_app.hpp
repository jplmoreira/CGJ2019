#pragma once

#include "include.hpp"

namespace engine {
	struct i_app {
		virtual void window_close_callback(GLFWwindow* win) = 0;
		virtual void window_size_callback(GLFWwindow* win, int winx, int winy) = 0;
		virtual void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) = 0;
		virtual void mouse_callback(GLFWwindow* win, double xpos, double ypos) = 0;
		virtual void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) = 0;

		virtual void setup(int winx, int winy) = 0;
		virtual void display(float elapsed_sec) = 0;
	};
}