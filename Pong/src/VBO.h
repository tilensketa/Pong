#pragma once

#include <glad/glad.h>
#include <vector>

#include "Vertex.h"

class VBO {
public:
	GLuint ID;
	VBO(std::vector<Vertex>& vertices);

	void Bind();
	void Unbind();
	void Delete();
};