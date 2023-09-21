#pragma once

#include <glad/glad.h>

#include "Shader.h"

class Texture {
public:
	Texture();
	Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	void Bind();
	void Unbind();
	void Delete();

private:
	GLuint m_ID;
	GLenum m_Type;
};