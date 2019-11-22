#include <fstream>
#include <iostream>

#include "shader.hpp"
#include "camera.hpp"

std::string engine::shader::read_shader(std::string file_name) {
    std::string str;

    std::ifstream infile(file_name.c_str(), std::ios::in);
    if(!infile.is_open())
        throw std::exception(("Unable to open " + file_name).c_str());

    infile.seekg(0, std::ios::end);
    str.reserve(infile.tellg());
    infile.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(infile)),
        std::istreambuf_iterator<char>());

    return str;
}

engine::shader::shader(std::string vert_file, std::string frag_file) {
    std::string vertex_shader = read_shader(vert_file);
    GLuint vertex_shdr_id = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vscode = vertex_shader.c_str();
    glShaderSource(vertex_shdr_id, 1, &vscode, 0);
    glCompileShader(vertex_shdr_id);

    std::string fragment_shader = read_shader(frag_file);
    GLuint fragment_shdr_id = glCreateShader(GL_FRAGMENT_SHADER);
    const GLchar* fscode = fragment_shader.c_str();
    glShaderSource(fragment_shdr_id, 1, &fscode, 0);
    glCompileShader(fragment_shdr_id);

    program_id = glCreateProgram();
    glAttachShader(program_id, vertex_shdr_id);
    glAttachShader(program_id, fragment_shdr_id);

    glBindAttribLocation(program_id, engine::ATTR::VERTICES, "in_position");

    glLinkProgram(program_id);
    uniforms["ModelMatrix"] = glGetUniformLocation(program_id, "ModelMatrix");
    uniforms["in_color"] = glGetUniformLocation(program_id, "in_color");
    GLint ubo_id = glGetUniformBlockIndex(program_id, "SharedMatrices");
    blocks["SharedMatrices"] = 0;
    glUniformBlockBinding(program_id, ubo_id, blocks["SharedMatrices"]);

    glDetachShader(program_id, vertex_shdr_id);
    glDeleteShader(vertex_shdr_id);
    glDetachShader(program_id, fragment_shdr_id);
    glDeleteShader(fragment_shdr_id);

#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not create shader.");
#endif
}

engine::shader::~shader() {
    glUseProgram(0);
    glDeleteProgram(program_id);
#ifndef ERROR_CALLBACK
    checkOpenGLError("ERROR: Could not destroy shaders.");
#endif
}

GLuint engine::shader::get_id() {
    return program_id;
}

void engine::shader::enable() {
    glUseProgram(program_id);
    camera::get_instance()->enable_block(blocks["SharedMatrices"]);
}