#pragma once

#include "include.hpp"

namespace engine {
	struct texture {
		GLuint id;
		std::string sampler;

		texture(std::string file, std::string sampler);
	};
}