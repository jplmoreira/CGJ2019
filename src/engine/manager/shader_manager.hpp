#pragma once

#include "i_manager.hpp"
#include "../shader.hpp"

namespace engine {
    namespace manager {
        struct shader_manager : i_manager<shader> {};
    }
}

std::shared_ptr<engine::manager::i_manager<engine::shader>> engine::manager::i_manager<engine::shader>::instance;