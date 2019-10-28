///////////////////////////////////////////////////////////////////////////////
//
// Drawing two instances of a triangle in Modern OpenGL.
// A "hello world" of Modern OpenGL.
//
// Assignment : Create Shader Abstraction 
//					(e.g. check compilation/linkage for errors, read from file) 
//			  : Manage Multiple Drawable Entities (using your vertex and matrix classes)
//              Draw a set of 7 TANs (i.e. TANGRAM shapes) of different colors: 
//              (1) 3 different TAN geometric shapes at the origin:
//					- right triangle
//					- square
//					- parallelogram
//              (2) 7 TANs of different colors put together to form a shape of
//                  your choice through transformation matrices:
//					- 2 big right triangles
//					- 1 medium right triangle
//					- 2 small right triangles
//					- 1 square
//					- 1 parallelogram;
//
// (c)2013-19 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <array>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "engine/math/vectors.hpp"
#include "engine/math/matrices.hpp"
#include "engine/math/mat_fact.hpp"

#define VERTICES 0
#define COLORS 1
#define OBJS 1

int indices[OBJS];
engine::math::mat4 transforms[OBJS];
GLuint VaoId[OBJS], VboId[3];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;

#define ERROR_CALLBACK
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

/////////////////////////////////////////////////////////////////////// SHADERs

const GLchar* VertexShader =
{
    "#version 330 core\n"

    "in vec4 in_Position;\n"
    "in vec4 in_Color;\n"
    "out vec4 ex_Color;\n"

    "uniform mat4 Matrix;\n"

    "void main(void)\n"
    "{\n"
    "	gl_Position = Matrix * in_Position;\n"
    "	ex_Color = in_Color;\n"
    "}\n"
};

const GLchar* FragmentShader =
{
    "#version 330 core\n"

    "in vec4 ex_Color;\n"
    "out vec4 out_Color;\n"

    "void main(void)\n"
    "{\n"
    "	out_Color = ex_Color;\n"
    "}\n"
};

void createShaderProgram() {
    VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShaderId, 1, &VertexShader, 0);
    glCompileShader(VertexShaderId);

    FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShaderId, 1, &FragmentShader, 0);
    glCompileShader(FragmentShaderId);

    ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId);
    glAttachShader(ProgramId, FragmentShaderId);

    glBindAttribLocation(ProgramId, VERTICES, "in_Position");
    glBindAttribLocation(ProgramId, COLORS, "in_Color");

    glLinkProgram(ProgramId);
    UniformId = glGetUniformLocation(ProgramId, "Matrix");

    glDetachShader(ProgramId, VertexShaderId);
    glDeleteShader(VertexShaderId);
    glDetachShader(ProgramId, FragmentShaderId);
    glDeleteShader(FragmentShaderId);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void destroyShaderProgram() {
    glUseProgram(0);
    glDeleteProgram(ProgramId);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

engine::math::vec4 purple(163.0f / 255.0f, 92.0f / 255.0f, 189.0f / 255.0f, 1.0f);
engine::math::vec4 yellow(240.0f / 255.0f, 222.0f / 255.0f, 51.0f / 255.0f, 1.0f);
engine::math::vec4 red(223.0f / 255.0f, 86.0f / 255.0f, 86.0f / 255.0f, 1.0f);
engine::math::vec4 blue(86.0f / 255.0f, 116.0f / 255.0f, 223.0f / 255.0f, 1.0f);
engine::math::vec4 green(62.0f / 255.0f, 137.0f / 255.0f, 98.0f / 255.0f, 1.0f);
engine::math::vec4 brown(126.0f / 255.0f, 83.0f / 255.0f, 60.0f / 255.0f, 1.0f);
engine::math::vec4 teal(19.0f / 255.0f, 111.0f / 255.0f, 114.0f / 255.0f, 1.0f);

float v_triangle[3][4] = {
    { 0.0f, 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 0.0f, 1.0f },
    { 0.0f, 1.0f, 0.0f, 1.0f }
};
GLushort i_triangle[3] = {0,1,2};

float v_square[4][4] = {
    { 0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.5f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.0f, 1.0f },
    { 0.5f, -0.5f, 0.0f, 1.0f }
};

GLushort i_square[6] = { 0, 1, 2, 0, 2, 3 };

float v_para[4][4] = {
    { 0.25f, 0.5f, 0.0f, 1.0f },
    { -0.5f, 0.5f, 0.0f, 1.0f },
    { -0.25f, -0.5f, 0.0f, 1.0f },
    { 0.5f, -0.5f, 0.0f, 1.0f }
};

GLushort i_para[6] = { 0, 1, 2, 0, 2, 3 };

void create_square(int i, const engine::math::vec4& color) {
    indices[i] = 6;
    glGenVertexArrays(1, &VaoId[i]);
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(3, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(v_square), v_square, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
        {
            float color_v[4][4]{
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_v), color_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i_square), i_square, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void create_parallelogram(int i, const engine::math::vec4& color) {
    indices[i] = 6;
    glGenVertexArrays(1, &VaoId[i]);
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(3, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(v_para), v_para, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
        {
            float color_v[4][4]{
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_v), color_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i_para), i_para, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void create_triangle(int i, const engine::math::vec4& color) {
    indices[i] = 3;
    glGenVertexArrays(1, &VaoId[i]);
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(3, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(v_triangle), v_triangle, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
        {
            float color_v[3][4]{
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(color_v), color_v, GL_STATIC_DRAW);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(i_triangle), i_triangle, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

template<std::size_t SIZE_V, std::size_t SIZE_I>
void create_object(int i, float (&vertices)[SIZE_V][4],
    GLushort (&indices)[SIZE_I], engine::math::vec4 color) {
    indices[i] = SIZE_I;
    std::cout << "vertices: " << SIZE_V << ", indices: " << SIZE_I << std::endl;

    glGenVertexArrays(1, &VaoId[i]);
    glBindVertexArray(VaoId[i]);
    {
        glGenBuffers(3, VboId);

        glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(VERTICES);
            glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
        {
            float v_color[4][4]{
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w},
                {color.x, color.y, color.z, color.w}
            };
            glBufferData(GL_ARRAY_BUFFER, sizeof(v_color), v_color, GL_STATIC_DRAW);
            glEnableVertexAttribArray(COLORS);
            glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, 0, 0);
        }
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[2]);
        {
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        }
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void createBufferObjects() {
    engine::math::vec3 z_axis(0.0f, 0.0f, 1.0f);

    create_object(0, v_square, i_square, engine::math::vec4(1.0f));
    transforms[0] =
        engine::math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
        engine::math::mat_fact::rodr_rot(45.0f, z_axis) *
        engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);

    //create_square(0, purple);
    //transforms[0] =
    //    engine::math::mat_fact::translate(0.0f, -0.35f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(45.0f, z_axis) *
    //    engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);

    //create_triangle(1, yellow);
    //transforms[1] =
    //    engine::math::mat_fact::translate(0.265f, -0.35f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(45.0f, z_axis);

    //create_triangle(2, red);
    //transforms[2] =
    //    engine::math::mat_fact::translate(0.0f, -0.085f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(135.0f, z_axis) *
    //    engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);

    //create_triangle(3, blue);
    //transforms[3] =
    //    engine::math::mat_fact::translate(-0.266f, 0.179f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(180.0f, z_axis) *
    //    engine::math::mat_fact::scale(0.71f, 0.71f, 1.0f);

    //create_triangle(4, green);
    //transforms[4] =
    //    engine::math::mat_fact::translate(-0.27f, 0.71f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(225.0f, z_axis);

    //create_parallelogram(5, brown);
    //transforms[5] =
    //    engine::math::mat_fact::translate(0.436f, 0.272f, 0.0f) *
    //    engine::math::mat_fact::scale(0.95f, 0.243f, 1.0f);

    //create_triangle(6, teal);
    //transforms[6] =
    //    engine::math::mat_fact::translate(0.35f, 0.63f, 0.0f) *
    //    engine::math::mat_fact::rodr_rot(225.0f, z_axis) *
    //    engine::math::mat_fact::scale(0.5f, 0.5f, 1.0f);

    //for(int i = 0; i < OBJS; i++) {
    //    transforms[i] = transforms[i] *
    //        engine::math::mat_fact::scale(0.75, 0.75, 1.0f);
    //}

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
#endif
}

void destroyBufferObjects() {
    for(int i = 0; i < OBJS; i++) {
        glBindVertexArray(VaoId[i]);
        glDisableVertexAttribArray(VERTICES);
        glDisableVertexAttribArray(COLORS);
        glDeleteBuffers(2, VboId);
        glDeleteVertexArrays(1, &VaoId[i]);
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
    for(int i = 0; i < OBJS; i++) {
        glBindVertexArray(VaoId[i]);
        glUseProgram(ProgramId);

        glUniformMatrix4fv(UniformId, 1, GL_FALSE, transforms[i].data);
        glDrawElements(GL_TRIANGLES, indices[i], GL_UNSIGNED_SHORT, (GLvoid*)0);

        glUseProgram(0);
        glBindVertexArray(0);
    }

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not draw scene.");
#endif
}

///////////////////////////////////////////////////////////////////// CALLBACKS

void window_close_callback(GLFWwindow* win) {
    destroyShaderProgram();
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
    createShaderProgram();
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
        640, 640, "Hello Modern 2D World", is_fullscreen, is_vsync);
    run(win);
    exit(EXIT_SUCCESS);
}

/////////////////////////////////////////////////////////////////////////// END