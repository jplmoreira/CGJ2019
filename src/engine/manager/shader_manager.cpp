#include "shader_manager.hpp"

std::shared_ptr<engine::manager::i_manager<engine::shader>> engine::manager::i_manager<engine::shader>::instance;

void engine::manager::shader_manager::destroy() {
    for(auto it = elements.begin(); it != elements.end(); ++it)
        it->second->destroy();
    elements.clear();
}
