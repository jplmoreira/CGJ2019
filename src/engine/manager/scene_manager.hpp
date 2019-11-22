#pragma once

#include "i_manager.hpp"
#include "../scene.hpp"

namespace engine {
    namespace manager {
        struct scene_manager : i_manager<scene> {};
    }
}

std::shared_ptr<engine::manager::i_manager<engine::scene>> engine::manager::i_manager<engine::scene>::instance;