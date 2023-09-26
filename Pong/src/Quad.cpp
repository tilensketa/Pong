#include "Quad.h"

#include "EBO.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Quad::Quad(glm::vec2 position, glm::vec2 size, const Texture& texture)
	: m_Size(size), m_Position(position) {
	m_Vertices.resize(4);
	m_Vertices[0] = Vertex(glm::vec3(-size.x / 2, -size.y / 2, 0.0f), glm::vec2(0.0f, 0.0f));
	m_Vertices[1] = Vertex(glm::vec3(-size.x / 2, size.y / 2, 0.0f), glm::vec2(0.0f, 1.0f));
	m_Vertices[2] = Vertex(glm::vec3(size.x / 2, size.y / 2, 0.0f), glm::vec2(1.0f, 1.0f));
	m_Vertices[3] = Vertex(glm::vec3(size.x / 2, -size.y / 2, 0.0f), glm::vec2(1.0f, 0.0f));
	m_Texture = texture;

	VAO.Bind();
	VBO VBO(m_Vertices);
	EBO EBO(m_Indices);
	// Position, color, texCoord
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

Quad::Quad(glm::vec2 position, glm::vec2 size)
	: m_Size(size), m_Position(position) {
	m_Vertices.resize(4);
	m_Vertices[0] = Vertex(glm::vec3(-size.x / 2, -size.y / 2, 0.0f), glm::vec2(0.0f, 0.0f));
	m_Vertices[1] = Vertex(glm::vec3(-size.x / 2,  size.y / 2, 0.0f), glm::vec2(0.0f, 1.0f));
	m_Vertices[2] = Vertex(glm::vec3( size.x / 2,  size.y / 2, 0.0f), glm::vec2(1.0f, 1.0f));
	m_Vertices[3] = Vertex(glm::vec3( size.x / 2, -size.y / 2, 0.0f), glm::vec2(1.0f, 0.0f));
	m_Texture = Texture();

	VAO.Bind();
	VBO VBO(m_Vertices);
	EBO EBO(m_Indices);
	// Position, color, texCoord
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}

void Quad::Draw(Shader& shader, Camera& camera) {
	shader.Activate();
	VAO.Bind();

	m_Texture.texUnit(shader, "tex0", 0);
	m_Texture.Bind();

	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.m_Position.x, camera.m_Position.y, camera.m_Position.z);
	camera.Matrix(shader, "camMatrix");

	glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(m_Position, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	glDrawElements(GL_TRIANGLES, (GLsizei)m_Indices.size(), GL_UNSIGNED_INT, 0);
}

void Quad::SetPosition(const glm::vec2 position) {
	m_Position = position;
}