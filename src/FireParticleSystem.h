#pragma once

#include "common.h"
#include "FireParticle.h"
#include "MineCraftBlock.h"

#include <vector>

class FireParticleSystem
{
public:
	FireParticleSystem(int numOfParticles, GLuint modelUniformLocation, MineCraftBlock *mcBlock, glm::vec3 startLocation, GLuint positionAttribLocation, GLuint colorIntensityAttribLocation, GLuint baseColorUniformLocation);

	void display();

	void update();

	~FireParticleSystem();

private:
	int numOfParticles;
	std::vector<FireParticle*> *particles;

	GLuint modelUniformLocation;
	GLuint positionAttribLocation;
	GLuint colorIntensityAttribLocation;
	GLuint baseColorUniformLocation;
	MineCraftBlock *mcBlock;
	glm::vec3 startLocation;

	FireParticle* createNewParticle();

	glm::vec3 getFireParticleColor(FireParticle *fp);
};