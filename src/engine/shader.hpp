#pragma once

#include <map>
#include <string>
#include <memory>

#include "include.hpp"

namespace engine {
    class shader {
        GLuint program_id = 0;
        std::string read_shader(std::string file_name);

    public:
        std::map<std::string, GLint> uniforms;
        std::map<std::string, GLuint> blocks;

        shader();
        shader(std::string vert_file, std::string frag_file);

        GLuint get_id();
        void enable();
        void destroy();
    };
}