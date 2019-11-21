#pragma once

#include <map>
#include <memory>
#include <string>

namespace engine {
    namespace manager {
        template<typename T>
        class i_manager {
        protected:
            static std::shared_ptr<i_manager<T>> instance;
            virtual void destroy();
        public:
            static std::shared_ptr<i_manager<T>> get_instance();
            static void free_instance();
            std::map<std::string, T> elements;
        };

        template<typename T>
        inline void i_manager<T>::destroy() {}
        template<typename T>
        inline std::shared_ptr<i_manager<T>> i_manager<T>::get_instance() {
            if(!instance) instance = std::make_shared<i_manager<T>>();
            return instance;
        }
        template<typename T>
        inline void i_manager<T>::free_instance() {
            instance->destroy();
            instance = nullptr;
        }
    }
}