#include "FireParticle.h"

// generate random float number between two float values
GLfloat FireParticle::randBetween(GLfloat hi, GLfloat low)
{
	return low + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (hi - low)));
}

FireParticle::FireParticle(GLuint modelUniformLocation, MineCraftBlock *mcBlock, glm::vec3 startLocation)
{
	this->modelUniformLocation = modelUniformLocation;
	this->mcBlock = mcBlock;
	this->startLocation = startLocation;

	// generate random particle values
	restart();
}

void FireParticle::restart()
{
	location = startLocation;
	velocity = randBetween(MIN_VELOCITY, MAX_VELOCITY);
	rotationalVelocity = randBetween(MIN_ROTATIONAL_VELOCITY, MAX_ROTATIONAL_VELOCITY);
	angle = 0.0f;
	direction = glm::vec3(
		randBetween(MIN_X_DIRECTION, MAX_X_DIRECTION),
		randBetween(MIN_Y_DIRECTION, MAX_Y_DIRECTION),
		randBetween(MIN_Z_DIRECTION, MAX_Z_DIRECTION)
	);
	axisOfRotation = glm::vec3(
		randBetween(MIN_X_AXIS_OF_ROTATION, MAX_X_AXIS_OF_ROTATION),
		randBetween(MIN_Y_AXIS_OF_ROTATION, MAX_Y_AXIS_OF_ROTATION),
		randBetween(MIN_Z_AXIS_OF_ROTATION, MAX_Z_AXIS_OF_ROTATION)
	);
	size = randBetween(MIN_SIZE, MAX_SIZE);
	ttl = randBetween(MIN_TTL, MAX_TTL);
}

// display the particle
void FireParticle::display()
{
	glm::mat4 model;
	model = glm::translate(model, location);
	model = glm::rotate(model, glm::radians(angle), axisOfRotation);
	model = glm::scale(model, glm::vec3(size, size, size));

	mcBlock->display(model);

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

// initialize the particle
void FireParticle::init(GLuint positionAttribLocation, GLuint colorIntensityAttribLocation)
{
	mcBlock->init(positionAttribLocation, colorIntensityAttribLocation);
}

// update particle state/values (note tied to fps)
void FireParticle::update()
{
	// location
	glm::vec3 distanceTraveled = direction * velocity;
	location += distanceTraveled;

	// rotation
	angle += rotationalVelocity;
	if (angle >= 360.0f) {
		angle = 0.0f;
	}

	ttl--;
	if (ttl <= 0)
		ttl = 0;
}

// return true if particle should be dead
bool FireParticle::isDead()
{
	return ttl <= 0;
}

// get distance of the particle from some points 'startLocation'
GLfloat FireParticle::getDistance(glm::vec3 startLocation)
{
	return glm::length(location - startLocation);
}

// delete the particle
FireParticle::~FireParticle()
{
}
