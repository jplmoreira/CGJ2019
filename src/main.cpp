#include <vector>
#include <iostream>

#include "engine/include.hpp"

#include "engine/shader.hpp"
#include "engine/geometry/object.hpp"
#include "engine/geometry/geometry.hpp"

std::vector<engine::geometry::object> objs;

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

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects() {
    engine::math::vec3 z_axis(0.0f, 0.0f, 1.0f);

    engine::geometry::object obj = engine::geometry::create_object(v_square, i_square, purple);
    obj.transform =
        engine::math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
        engine::math::mat_fact::rodr_rot(45.0f, z_axis) *
        engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_triangle, i_triangle, yellow);
    obj.transform =
        engine::math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
        engine::math::mat_fact::rodr_rot(45.0f, z_axis);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_triangle, i_triangle, red);
    obj.transform =
        engine::math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
        engine::math::mat_fact::rodr_rot(135.0f, z_axis) *
        engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_triangle, i_triangle, blue);
    obj.transform =
        engine::math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
        engine::math::mat_fact::rodr_rot(180.0f, z_axis) *
        engine::math::mat_fact::scale(0.71f, 0.71f, 1.0f);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_triangle, i_triangle, green);
    obj.transform =
        engine::math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
        engine::math::mat_fact::rodr_rot(225.0f, z_axis);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_para, i_para, brown);
    obj.transform =
        engine::math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
        engine::math::mat_fact::scale(0.95f, 0.243f, 1.0f);
    objs.push_back(obj);

    obj = engine::geometry::create_object(v_triangle, i_triangle, teal);
    obj.transform =
        engine::math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
        engine::math::mat_fact::rodr_rot(225.0f, z_axis) *
        engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);
    objs.push_back(obj);

    for(auto &o : objs) {
        o.transform = o.transform *
            engine::math::mat_fact::scale(0.75, 0.75, 1.0f);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void destroyBufferObjects() {
    GLuint vbo[3];

    for(auto &o : objs) {
        glBindVertexArray(o.vao);
        glDisableVertexAttribArray(engine::ATTR::VERTICES);
        glDisableVertexAttribArray(engine::ATTR::COLORS);
        glDeleteBuffers(3, vbo);
        glDeleteVertexArrays(1, &o.vao);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
#endif
}

/////////////////////////////////////////////////////////////////////// SCENE

void drawScene() {
    for(auto &o : objs) {
        glBindVertexArray(o.vao);
        glUseProgram(engine::shader::get_instance()->get_id());

        glUniformMatrix4fv(engine::shader::get_instance()->get_uniform(), 1, GL_FALSE, o.transform.data);
        glDrawElements(GL_TRIANGLES, o.num_indexes, GL_UNSIGNED_SHORT, (GLvoid*)0);

        glUseProgram(0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win) {
    engine::shader::get_instance()->destroy();
    destroyBufferObjects();
}

void window_size_callback(GLFWwindow* win, int winx, int winy) {
    glViewport(0, 0, winx, winy);
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
    createBufferObjects();
    return win;
}

////////////////////////////////////////////////////////////////////////// RUN

void display(GLFWwindow* win, double elapsed_sec) {
    drawScene();
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
        1280, 1280, "Hello Modern 2D World", is_fullscreen, is_vsync);
    run(win);
    exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END