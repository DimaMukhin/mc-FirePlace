#pragma once

#include "common.h"
#include "Mesh.h"

#include <glm/glm.hpp>

namespace block {
	Mesh* createBlockMesh(glm::vec4 color);
}
