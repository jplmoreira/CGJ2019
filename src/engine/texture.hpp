#pragma once

#include "include.hpp"

namespace engine {
	struct texture {
		GLuint id;

		texture(std::string file);
		texture(GLuint id);
	};
}