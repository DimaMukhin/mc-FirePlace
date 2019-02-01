#include "Particle.h"

Particle::Particle(Mesh *block)
{
	this->block = block;
	direction = glm::vec3(0.0f, 1.0f, 0.0f);
	location = glm::vec3(0.0f, 0.0f, 0.0f);
	speed = 0.4f;
}

void Particle::display()
{
	glm::mat4 model;
	model = glm::translate(model, location);
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	block->display();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

void Particle::update()
{

}

void Particle::init(GLuint positionAttribLocation, GLuint colorAttribLocation, GLuint modelUniformLocation)
{
	this->modelUniformLocation = modelUniformLocation;
	block->init(positionAttribLocation, colorAttribLocation);
}

Particle::~Particle()
{

}
