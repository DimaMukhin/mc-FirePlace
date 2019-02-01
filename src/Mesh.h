#pragma once

#include "common.h"
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Mesh
{
public:
	Mesh();

	Mesh(glm::vec4 *vertices, glm::vec4 *colors, GLuint numOfVertices);

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	~Mesh();

private:
	GLuint VAO, VBO;
	GLuint numOfVertices;
	glm::vec4 *vertices, *colors;
};

