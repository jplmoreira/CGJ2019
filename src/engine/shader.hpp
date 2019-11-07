#pragma once

#include <memory>

#include "include.hpp"

namespace engine {
    class shader {
        static std::shared_ptr<shader> instance;
        GLuint program_id = 0;
        GLint uniform_id = 0;
        const GLuint block_pointer = 0;

        static std::string read_shader(std::string file_name);

    public:
        static std::shared_ptr<shader> get_instance() {
            if(!instance) instance = std::make_shared<shader>();
            return instance;
        }

        GLuint get_id();
        GLint get_uniform();
        const GLuint get_block_ptr();
        void load();
        void destroy();
    };
}