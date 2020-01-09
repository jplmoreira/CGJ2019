#pragma once

#include <map>
#include <string>
#include <memory>

#include "include.hpp"

namespace engine {
    class shader {
        GLuint program_id = 0;
		GLuint vertex_shdr_id = 0, fragment_shdr_id = 0;
        std::string read_shader(std::string file_name);

    public:
        std::map<std::string, GLint> uniforms;
        std::map<std::string, GLuint> blocks;

        shader(std::string vert_file, std::string frag_file);
		shader();
        ~shader();

		void compile(std::string vs, std::string fs);
		void cleanup();
        GLuint get_id();
        void enable();
        void disable();
    };
}