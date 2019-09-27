#pragma once

#include <sstream>
#include <iostream>
#include <iomanip>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "i_GLapp.h"

class GLengine {
	static GLengine* instance;

	GLengine() {}

public:
	static GLengine* get_instance() {
		if(!instance) instance = new GLengine();
		return instance;
	}

	GLFWwindow* setup(i_GLapp &app, int major, int minor,
		int winx, int winy, const char* title, int is_fullscreen, int is_vsync);

	void run(GLFWwindow* win);
};