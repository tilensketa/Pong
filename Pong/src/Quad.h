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
	Quad(float width, float height, const Texture& texture);
	Quad(float width, float height);

	void Draw(Shader& shader, Camera& camera);
	void Move(const glm::vec3 position);
private:
	glm::vec3 m_Position = glm::vec3(0.0f);
	float m_Width, m_Height;
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices = {
		0, 1, 2,
		0, 2, 3
	};
	Texture m_Texture;
	VAO VAO;
};