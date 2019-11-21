#pragma once

#include "i_manager.hpp"
#include "../shader.hpp"

namespace engine {
    namespace manager {
        struct shader_manager : i_manager<shader> {
            void destroy();
        };
    }
}