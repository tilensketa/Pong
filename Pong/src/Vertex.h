#pragma once

#include <glm/glm.hpp>

struct Vertex {
	Vertex() = default;

	Vertex(glm::vec3 position, glm::vec2 texCoord)
		: Position(position), TexCoord(texCoord) {}

	Vertex(glm::vec3 position, glm::vec3 color, glm::vec2 texCoord)
		: Position(position), Color(color), TexCoord(texCoord) {}

	glm::vec3 Position = glm::vec3(0.0f);
	glm::vec3 Color = glm::vec3(1.0f, 0.0f, 1.0f);
	glm::vec2 TexCoord = glm::vec2(0.0f);
};