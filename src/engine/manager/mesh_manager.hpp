#pragma once

#include "i_manager.hpp"
#include "../geometry/mesh.hpp"

namespace engine {
    namespace manager {
        struct mesh_manager : i_manager<geometry::mesh> {};
    }
}

std::shared_ptr<engine::manager::i_manager<engine::geometry::mesh>> engine::manager::i_manager<engine::geometry::mesh>::instance;