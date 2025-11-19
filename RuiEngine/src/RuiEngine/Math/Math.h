#pragma once

#include <glm/glm.hpp>

namespace RuiEngine::Math {

	std::tuple<bool, glm::vec3, glm::vec3, glm::vec3> DecomposeTransform(const glm::mat4& transform);

}