#pragma once

#include <memory>
#include <sstream>
#include <iomanip>

#include "include.hpp"

#include "i_app.hpp"

namespace engine {
	class gl_engine {
		static std::shared_ptr<gl_engine> instance;

	public:
		static std::shared_ptr<gl_engine> get_instance();

		std::unique_ptr<i_app> app;

		GLFWwindow* setup(int major, int minor, int winx, int winy, const char* title,
			int is_fullscreen, int is_vsync);
		GLFWwindow* setupGLFW(int major, int minor, int winx, int winy, const char* title,
			int is_fullscreen, int is_vsync);
		GLFWwindow* setupWindow(int winx, int winy, const char* title, int is_fullscreen,
			int is_vsync);
		void setupCallbacks(GLFWwindow* win);
		void setupGLEW();
		void setupOpenGL(int winx, int winy);
		void checkOpenGLInfo();
		void run(GLFWwindow* win);
		void updateFPS(GLFWwindow* win, double elapsed_sec);
	};
}