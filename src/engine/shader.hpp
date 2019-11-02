#pragma once

#include <memory>

#include "include.hpp"

namespace engine {
    class shader {
        static std::shared_ptr<shader> instance;
        GLuint program_id;
        GLint uniform_id;

        static std::string read_shader(std::string file_name);

    public:
        static std::shared_ptr<shader> get_instance() {
            if(!instance) instance = std::make_shared<shader>();
            return instance;
        }

        GLuint get_id();
        GLint get_uniform();
        void load();
        void destroy();
    };
}