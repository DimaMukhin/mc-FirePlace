#pragma once

#include "common.h"
#include "FireParticle.h"
#include "Mesh.h"

#include <vector>

class FireParticleSystem
{
public:
	FireParticleSystem(int numOfParticles, GLuint modelUniformLocation, Mesh *particleMesh, glm::vec3 startLocation, GLuint positionAttribLocation, GLuint colorAttribLocation);

	void display();

	void update();

	~FireParticleSystem();

private:
	int numOfParticles;
	std::vector<FireParticle*> *particles;

	GLuint modelUniformLocation;
	GLuint positionAttribLocation;
	GLuint colorAttribLocation;
	Mesh *particleMesh;
	glm::vec3 startLocation;

	FireParticle* createNewParticle();
};