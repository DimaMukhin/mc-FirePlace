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

	// generate particles
	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *newParticle = createNewParticle();
		particles->push_back(newParticle);
	}
}

// display all particles
void FireParticleSystem::display()
{
	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *fp = particles->at(i);
		glm::vec3 fpColor = getFireParticleColor(fp);
		glUniform4fv(baseColorUniformLocation, 1, glm::value_ptr(fpColor));
		fp->display();
	}
}

// update all particles (not tied to fps)
void FireParticleSystem::update()
{
	for (int i = 0; i < numOfParticles; i++) {
		FireParticle *currParticle = particles->at(i);
		currParticle->update();

		if (currParticle->isDead()) {
			currParticle->restart();
			/*particles->erase(particles->begin() + i);
			particles->push_back(createNewParticle());
			delete currParticle;*/
		}
	}
}

// delete fire particle system
FireParticleSystem::~FireParticleSystem()
{
}

// create a new particle for the system
FireParticle * FireParticleSystem::createNewParticle()
{
	FireParticle *newParticle = new FireParticle(modelUniformLocation, mcBlock, startLocation);
	newParticle->init(positionAttribLocation, colorIntensityAttribLocation);
	return newParticle;
}

// get fire particle color based on distance using lerp
glm::vec3 FireParticleSystem::getFireParticleColor(FireParticle * fp)
{
	glm::vec3 startColor = glm::vec3(1.0f, 0.5f, 0.1f);
	glm::vec3 endColor = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat endDistance = 1.5f;

	GLfloat fpDistance = fp->getDistance(startLocation);

	GLfloat t = fpDistance / endDistance;

	glm::vec3 currColor = (startColor * (1 - t)) + (t * endColor);

	return currColor;
}
