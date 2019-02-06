#include "FireParticleSystem.h"

FireParticleSystem::FireParticleSystem(int numOfParticles, GLuint modelUniformLocation, Mesh * particleMesh, glm::vec3 startLocation, GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	this->numOfParticles = numOfParticles;
	this->modelUniformLocation = modelUniformLocation;
	this->particleMesh = particleMesh;
	this->startLocation = startLocation;
	this->positionAttribLocation = positionAttribLocation;
	this->colorAttribLocation = colorAttribLocation;

	particles = new std::vector<FireParticle*>();

	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *newParticle = createNewParticle();
		particles->push_back(newParticle);
	}
}

void FireParticleSystem::display()
{
	for (int i = 0; i < numOfParticles; i++) {
		particles->at(i)->display();
	}
}

void FireParticleSystem::update()
{
	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *currParticle = particles->at(i);
		currParticle->update();

		if (currParticle->isDead()) {
			particles->erase(particles->begin() + i);
			particles->push_back(createNewParticle());
		}
	}
}

FireParticleSystem::~FireParticleSystem()
{
}

FireParticle * FireParticleSystem::createNewParticle()
{
	FireParticle *newParticle = new FireParticle(modelUniformLocation, particleMesh, startLocation);
	newParticle->init(positionAttribLocation, colorAttribLocation);
	return newParticle;
}
