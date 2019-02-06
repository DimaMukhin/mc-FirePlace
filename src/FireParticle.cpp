#include "FireParticle.h"

GLfloat FireParticle::randBetween(GLfloat hi, GLfloat low)
{
	return low + static_cast <GLfloat> (rand()) / (static_cast <GLfloat> (RAND_MAX / (hi - low)));
}

FireParticle::FireParticle(GLuint modelUniformLocation, Mesh *particleMesh, glm::vec3 location)
{
	this->modelUniformLocation = modelUniformLocation;
	this->particleMesh = particleMesh;
	this->location = location;

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

void FireParticle::display()
{
	glm::mat4 model;
	model = glm::translate(model, location);
	model = glm::rotate(model, glm::radians(angle), axisOfRotation);
	model = glm::scale(model, glm::vec3(size, size, size));

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));

	particleMesh->display();

	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(glm::mat4()));
}

void FireParticle::init(GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	particleMesh->init(positionAttribLocation, colorAttribLocation);
}

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

bool FireParticle::isDead()
{
	return ttl <= 0;
}

FireParticle::~FireParticle()
{
}
