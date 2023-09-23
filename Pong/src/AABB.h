#pragma once

#include <glm/glm.hpp>

struct AABB {
	glm::vec2 Min;
	glm::vec2 Max;

	AABB() = default;
	AABB(const glm::vec2& min, const glm::vec2& max)
		: Min(min), Max(max) {}
};