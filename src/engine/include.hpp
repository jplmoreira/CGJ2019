#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "math/vectors.hpp"
#include "math/matrices.hpp"
#include "math/mat_fact.hpp"

#define VERTICES 0
#define COLORS 1

GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId;