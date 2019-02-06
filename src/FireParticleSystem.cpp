#include "FireParticleSystem.h"

FireParticleSystem::FireParticleSystem(int numOfParticles, GLuint modelUniformLocation, MineCraftBlock *mcBlock, glm::vec3 startLocation, GLuint positionAttribLocation, GLuint colorIntensityAttribLocation, GLuint baseColorUniformLocation)
{
	this->numOfParticles = numOfParticles;
	this->modelUniformLocation = modelUniformLocation;
	this->mcBlock = mcBlock;
	this->startLocation = startLocation;
	this->positionAttribLocation = positionAttribLocation;
	this->colorIntensityAttribLocation = colorIntensityAttribLocation;
	this->baseColorUniformLocation = baseColorUniformLocation;

	particles = new std::vector<FireParticle*>();

	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *newParticle = createNewParticle();
		particles->push_back(newParticle);
	}
}

void FireParticleSystem::display()
{
	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *fp = particles->at(i);
		glm::vec3 fpColor = getFireParticleColor(fp);
		glUniform4fv(baseColorUniformLocation, 1, glm::value_ptr(fpColor));
		fp->display();
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
	FireParticle *newParticle = new FireParticle(modelUniformLocation, mcBlock, startLocation);
	newParticle->init(positionAttribLocation, colorIntensityAttribLocation);
	return newParticle;
}

glm::vec3 FireParticleSystem::getFireParticleColor(FireParticle * fp)
{
	glm::vec3 startColor = glm::vec3(1.0f, 0.3f, 0.0f);
	glm::vec3 endColor = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat endDistance = 2.0f;

	GLfloat fpDistance = fp->getDistance(startLocation);

	GLfloat t = fpDistance / endDistance;

	glm::vec3 currColor = (startColor * (1 - t)) + (t * endColor);

	return currColor;
}
