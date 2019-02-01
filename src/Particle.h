#pragma once

#include "common.h"
#include "Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Particle
{
public:
	Particle(Mesh *block);

	void display();

	void update();

	void init(GLuint positionAttribLocation, GLuint colorAttribLocation, GLuint modelUniformLocation);

	~Particle();

private:
	Mesh *block;
	glm::vec3 direction;
	glm::vec3 location;
	GLfloat speed;
	GLuint modelUniformLocation
};
