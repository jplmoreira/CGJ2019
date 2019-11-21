#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "engine/include.hpp"

#include "engine/camera.hpp"
#include "engine/shader.hpp"
#include "engine/scene.hpp"

#ifdef  ERROR_CALLBACK

////////////////////////////////////////////////// ERROR CALLBACK (OpenGL 4.3+)

static const std::string errorSource(GLenum source) {
    switch(source) {
    case GL_DEBUG_SOURCE_API:				return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:		return "window system";
    case GL_DEBUG_SOURCE_SHADER_COMPILER:	return "shader compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY:		return "third party";
    case GL_DEBUG_SOURCE_APPLICATION:		return "application";
    case GL_DEBUG_SOURCE_OTHER:				return "other";
    default:								exit(EXIT_FAILURE);
    }
}

static const std::string errorType(GLenum type) {
    switch(type) {
    case GL_DEBUG_TYPE_ERROR:				return "error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	return "deprecated behavior";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:	return "undefined behavior";
    case GL_DEBUG_TYPE_PORTABILITY:			return "portability issue";
    case GL_DEBUG_TYPE_PERFORMANCE:			return "performance issue";
    case GL_DEBUG_TYPE_MARKER:				return "stream annotation";
    case GL_DEBUG_TYPE_PUSH_GROUP:			return "push group";
    case GL_DEBUG_TYPE_POP_GROUP:			return "pop group";
    case GL_DEBUG_TYPE_OTHER_ARB:			return "other";
    default:								exit(EXIT_FAILURE);
    }
}

static const std::string errorSeverity(GLenum severity) {
    switch(severity) {
    case GL_DEBUG_SEVERITY_HIGH:			return "high";
    case GL_DEBUG_SEVERITY_MEDIUM:			return "medium";
    case GL_DEBUG_SEVERITY_LOW:				return "low";
    case GL_DEBUG_SEVERITY_NOTIFICATION:	return "notification";
    default:								exit(EXIT_FAILURE);
    }
}

static void error(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
    const GLchar* message, const void* userParam) {
    std::cerr << "GL ERROR:" << std::endl;
    std::cerr << "  source:     " << errorSource(source) << std::endl;
    std::cerr << "  type:       " << errorType(type) << std::endl;
    std::cerr << "  severity:   " << errorSeverity(severity) << std::endl;
    std::cerr << "  debug call: " << std::endl << message << std::endl;
    std::cerr << "Press <return>.";
    std::cin.ignore();
}

void setupErrorCallback() {
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(error, 0);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, GL_TRUE);
    // params: source, type, severity, count, ids, enabled
}

#else

///////////////////////////////////////////////// ERROR HANDLING (All versions)

static const std::string errorString(GLenum error) {
    switch(error) {
    case GL_NO_ERROR:
        return "No error has been recorded.";
    case GL_INVALID_ENUM:
        return "An unacceptable value is specified for an enumerated argument.";
    case GL_INVALID_VALUE:
        return "A numeric argument is out of range.";
    case GL_INVALID_OPERATION:
        return "The specified operation is not allowed in the current state.";
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "The framebuffer object is not complete.";
    case GL_OUT_OF_MEMORY:
        return "There is not enough memory left to execute the command.";
    case GL_STACK_UNDERFLOW:
        return "An attempt has been made to perform an operation that would cause an internal stack to underflow.";
    case GL_STACK_OVERFLOW:
        return "An attempt has been made to perform an operation that would cause an internal stack to overflow.";
    default: exit(EXIT_FAILURE);
    }
}

static bool isOpenGLError() {
    bool isError = false;
    GLenum errCode;
    while((errCode = glGetError()) != GL_NO_ERROR) {
        isError = true;
        std::cerr << "OpenGL ERROR [" << errorString(errCode) << "]." << std::endl;
    }
    return isError;
}

static void checkOpenGLError(std::string error) {
    if(isOpenGLError()) {
        std::cerr << error << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif // ERROR_CALLBACK

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win) {
    engine::shader::get_instance()->destroy();
    engine::camera::get_instance()->destroy_block();
    engine::scene::get_instance()->delete_objects();
}

void window_size_callback(GLFWwindow* win, int winx, int winy) {
    engine::camera::get_instance()->resize(winx, winy);
    glViewport(0, 0, winx, winy);
}

void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
        window_close_callback(win);
    } else if(key == GLFW_KEY_W && action == GLFW_PRESS) {
        engine::camera::get_instance()->move(engine::camera::DIR::UP);
    } else if(key == GLFW_KEY_W && action == GLFW_RELEASE) {
        engine::camera::get_instance()->move(engine::camera::DIR::STOP);
    } else if(key == GLFW_KEY_S && action == GLFW_PRESS) {
        engine::camera::get_instance()->move(engine::camera::DIR::DOWN);
    } else if(key == GLFW_KEY_S && action == GLFW_RELEASE) {
        engine::camera::get_instance()->move(engine::camera::DIR::STOP);
    } else if(key == GLFW_KEY_D && action == GLFW_PRESS) {
        engine::camera::get_instance()->move(engine::camera::DIR::RIGHT);
    } else if(key == GLFW_KEY_D && action == GLFW_RELEASE) {
        engine::camera::get_instance()->move(engine::camera::DIR::STOP);
    } else if(key == GLFW_KEY_A && action == GLFW_PRESS) {
        engine::camera::get_instance()->move(engine::camera::DIR::LEFT);
    } else if(key == GLFW_KEY_A && action == GLFW_RELEASE) {
        engine::camera::get_instance()->move(engine::camera::DIR::STOP);
    } else if(key == GLFW_KEY_P && action == GLFW_PRESS) {
        engine::camera::get_instance()->change_project(true);
    } else if(key == GLFW_KEY_P && action == GLFW_RELEASE) {
        engine::camera::get_instance()->change_project(false);
    } else if(key == GLFW_KEY_G && action == GLFW_PRESS) {
        engine::camera::get_instance()->toggle_gimbal();
    }
}

void mouse_callback(GLFWwindow* win, double xpos, double ypos) {
    engine::camera::get_instance()->rotate((float)xpos, (float)ypos);
}

void mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        engine::camera::get_instance()->activate_rotation(true);
    } else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        engine::camera::get_instance()->activate_rotation(false);
    }
}

///////////////////////////////////////////////////////////////////////// SETUP

void glfw_error_callback(int error, const char* description) {
    std::cerr << "GLFW Error: " << description << std::endl;
}

GLFWwindow* setupWindow(int winx, int winy, const char* title,
    int is_fullscreen, int is_vsync) {
    GLFWmonitor* monitor = is_fullscreen ? glfwGetPrimaryMonitor() : 0;
    GLFWwindow* win = glfwCreateWindow(winx, winy, title, monitor, 0);
    if(!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(win);
    glfwSwapInterval(is_vsync);
    return win;
}

void setupCallbacks(GLFWwindow* win) {
    glfwSetWindowCloseCallback(win, window_close_callback);
    glfwSetWindowSizeCallback(win, window_size_callback);

    glfwSetKeyCallback(win, key_callback);
    glfwSetCursorPosCallback(win, mouse_callback);
    glfwSetMouseButtonCallback(win, mouse_button_callback);
}

GLFWwindow* setupGLFW(int gl_major, int gl_minor,
    int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()) {
        exit(EXIT_FAILURE);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, gl_major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, gl_minor);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* win = setupWindow(winx, winy, title, is_fullscreen, is_vsync);
    setupCallbacks(win);

#if _DEBUG
    std::cout << "GLFW " << glfwGetVersionString() << std::endl;
#endif
    return win;
}

void setupGLEW() {
    glewExperimental = GL_TRUE;
    // Allow extension entry points to be loaded even if the extension isn't 
    // present in the driver's extensions string.
    GLenum result = glewInit();
    if(result != GLEW_OK) {
        std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
        exit(EXIT_FAILURE);
    }
    GLenum err_code = glGetError();
    // You might get GL_INVALID_ENUM when loading GLEW.
}

void checkOpenGLInfo() {
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cerr << "OpenGL Renderer: " << renderer << " (" << vendor << ")" << std::endl;
    std::cerr << "OpenGL version " << version << std::endl;
    std::cerr << "GLSL version " << glslVersion << std::endl;
}

void setupOpenGL(int winx, int winy) {
#if _DEBUG
    checkOpenGLInfo();
#endif
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glDepthRange(0.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glViewport(0, 0, winx, winy);
}

GLFWwindow* setup(int major, int minor,
    int winx, int winy, const char* title, int is_fullscreen, int is_vsync) {
    GLFWwindow* win =
        setupGLFW(major, minor, winx, winy, title, is_fullscreen, is_vsync);
    setupGLEW();
    setupOpenGL(winx, winy);
#ifdef ERROR_CALLBACK
    setupErrorCallback();
#endif
    engine::shader::get_instance()->load();
    engine::camera::get_instance()->create_block();
    engine::scene::get_instance()->create_objects();
    engine::camera::get_instance()->setup(false, winx, winy, 30.0f, 1.0f, 100.0f);
    engine::camera::get_instance()->look_at(engine::math::vec3(0.0f, 0.0f, 5.0f),
        engine::math::vec3(0.0f, 0.0f, 0.0f),
        engine::math::vec3(0.0f, 1.0f, 0.0f));
    return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void updateFPS(GLFWwindow* win, double elapsed_sec) {
    static unsigned int acc_frames = 0;
    static double acc_time = 0.0;
    const double UPDATE_TIME = 1.0;

    ++acc_frames;
    acc_time += elapsed_sec;
    if(acc_time > UPDATE_TIME) {
        std::ostringstream oss;
        double fps = acc_frames / acc_time;
        oss << std::fixed << std::setw(5) << std::setprecision(1) << fps << " FPS";
        glfwSetWindowTitle(win, oss.str().c_str());

        acc_frames = 0;
        acc_time = 0.0;
    }
}

void display(GLFWwindow* win, double elapsed_sec) {
    updateFPS(win, elapsed_sec);
    engine::camera::get_instance()->calculate_camera((float)elapsed_sec);
    engine::scene::get_instance()->draw();
}

void run(GLFWwindow* win) {
    double last_time = glfwGetTime();
    while(!glfwWindowShouldClose(win)) {
        double time = glfwGetTime();
        double elapsed_time = time - last_time;
        last_time = time;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        display(win, elapsed_time);
        glfwSwapBuffers(win);
        glfwPollEvents();
#ifndef ERROR_CALLBACK
        checkOpenGLError("ERROR: MAIN/RUN");
#endif
    }
    glfwDestroyWindow(win);
    glfwTerminate();
}

////////////////////////////////////////////////////////////////////////// MAIN

int main(int argc, char* argv[]) {
    int gl_major = 4, gl_minor = 3;
    int is_fullscreen = 0;
    int is_vsync = 1;
    GLFWwindow* win = setup(gl_major, gl_minor,
        1280, 1000, "CGJ Project", is_fullscreen, is_vsync);
    run(win);
    exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END