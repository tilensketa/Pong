#pragma once

#include <glad/glad.h>

#include <vector>

class EBO {
public:
	GLuint ID;
	EBO(std::vector<uint32_t>& indices);

	void Bind();
	void Unbind();
	void Delete();
};