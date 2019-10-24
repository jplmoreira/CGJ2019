#include "shader.hpp"

const char* vertex_shader =
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

const char* fragment_shader =
{
    "#version 330 core\n"

    "in vec4 ex_Color;\n"
    "out vec4 out_Color;\n"

    "void main(void)\n"
    "{\n"
    "	out_Color = ex_Color;\n"
    "}\n"
};

void engine::shader::setup() {
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader, 0);
    glCompileShader(vertex_shader_id);

    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader, 0);
    glCompileShader(fragment_shader_id);

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shader_id);
    glAttachShader(program_id, fragment_shader_id);

    glBindAttribLocation(program_id, ATTR::VERTICES, "in_Position");
    glBindAttribLocation(program_id, ATTR::COLORS, "in_Color");

    glLinkProgram(program_id);
    transform_id = glGetUniformLocation(program_id, "Matrix");

    glDetachShader(program_id, vertex_shader_id);
    glDeleteShader(vertex_shader_id);
    glDetachShader(program_id, fragment_shader_id);
    glDeleteShader(fragment_shader_id);
}

void engine::shader::destroy() {
    glUseProgram(0);
    glDeleteProgram(program_id);
}
