#include <fstream>
#include <iostream>

#include "shader.hpp"

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

std::shared_ptr<engine::shader> engine::shader::instance;

const char* engine::shader::read_shader(std::string file_name) {
    std::string str;

    std::ifstream infile(file_name.c_str(), std::ios::in);
    if(!infile.is_open())
        throw std::exception(("Unable to open " + file_name).c_str());

    infile.seekg(0, std::ios::end);
    str.reserve(infile.tellg());
    infile.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(infile)),
        std::istreambuf_iterator<char>());

    return str.c_str();
}

GLuint engine::shader::get_id() {
    return program_id;
}

GLint engine::shader::get_uniform() {
    return uniform_id;
}

void engine::shader::load() {
    const char* vertex_shader = read_shader("res/shaders/vertex.glsl");
    GLuint vertex_shdr_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shdr_id, 1, &VertexShader, 0);
    glCompileShader(vertex_shdr_id);

    const char* fragment_shader = read_shader("res/shaders/fragment.glsl");
    GLuint fragment_shdr_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shdr_id, 1, &FragmentShader, 0);
    glCompileShader(fragment_shdr_id);

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shdr_id);
    glAttachShader(program_id, fragment_shdr_id);

    glBindAttribLocation(program_id, engine::ATTR::VERTICES, "in_position");
    glBindAttribLocation(program_id, engine::ATTR::COLORS, "in_color");

    glLinkProgram(program_id);
    uniform_id = glGetUniformLocation(program_id, "Matrix");

    glDetachShader(program_id, vertex_shdr_id);
    glDeleteShader(vertex_shdr_id);
    glDetachShader(program_id, fragment_shdr_id);
    glDeleteShader(fragment_shdr_id);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create shaders.");
#endif
}

void engine::shader::destroy() {
    glUseProgram(0);
    glDeleteProgram(program_id);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}
