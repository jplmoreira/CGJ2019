#include "i_GLapp.h"
#include "GLengine.h"

///////////////////////////////////////////////////////////////////// CALLBACKS

class app : i_GLapp {
public:
	void window_close_callback(GLFWwindow* win) {
		std::cout << "closing..." << std::endl;
	}

	void window_size_callback(GLFWwindow* win, int winx, int winy) {
		std::cout << "size: " << winx << " " << winy << std::endl;
		glViewport(0, 0, winx, winy);
	}

	void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
		std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
		if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(win, GLFW_TRUE);
			app::window_close_callback(win);
		}
	}

	void mouse_callback(GLFWwindow* win, double xpos, double ypos) {
		std::cout << "mouse: " << xpos << " " << ypos << std::endl;
	}

	void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
		std::cout << "button: " << button << " " << action << " " << mods << std::endl;
	}

	void scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
		std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
	}

	void joystick_callback(int jid, int event) {
		std::cout << "joystick: " << jid << " " << event << std::endl;
	}
};

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[])
{
	int gl_major = 4, gl_minor = 3;
	int is_fullscreen = 0;
	int is_vsync = 2;
	app my_app;
	GLengine *engine = GLengine::get_instance();
	GLFWwindow* win = engine->setup(&my_app, gl_major, gl_minor, 
		640, 480, "OpenGL Viewer (GLFW)", is_fullscreen, is_vsync);
	engine->run(win);
	exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END