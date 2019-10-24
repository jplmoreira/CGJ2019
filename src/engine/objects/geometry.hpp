#pragma once

#include "object.hpp"
#include "../math/vectors.hpp"
#include "../vertex_attr.hpp"

namespace engine {
    namespace objects {
        object create_triangle(const math::vec4& color);
        object create_square(const math::vec4& color);
        object create_parallelogram(const math::vec4& color);
    }
}