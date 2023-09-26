#pragma once

#include "Vertex.h"
#include"VAO.h"
#include"Camera.h"
#include"Texture.h"

#include <glm/glm.hpp>
#include <vector>

class Quad {
public:
	Quad() = default;
	Quad(glm::vec2 position, glm::vec2 size, const Texture& texture);
	Quad(glm::vec2 position, glm::vec2 size);

	void Draw(Shader& shader, Camera& camera);
	void SetPosition(const glm::vec2 position);

private:
	glm::vec2 m_Position = glm::vec2(0.0f);
	glm::vec2 m_Size = glm::vec2(10.0f, 10.0f);
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices = {
		0, 1, 2,
		0, 2, 3
	};
	Texture m_Texture;
	VAO VAO;
};