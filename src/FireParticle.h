#pragma once

#include "common.h"
#include "MineCraftBlock.h"

#include <glm/gtc/type_ptr.hpp>

#define MIN_VELOCITY 0.01f
#define MAX_VELOCITY 0.1f

#define MIN_ROTATIONAL_VELOCITY 0.8f
#define MAX_ROTATIONAL_VELOCITY 5.0f

#define MIN_X_DIRECTION -1.0f
#define MAX_X_DIRECTION 1.0f
#define MIN_Y_DIRECTION 0.45f
#define MAX_Y_DIRECTION 1.0f
#define MIN_Z_DIRECTION -1.0f
#define MAX_Z_DIRECTION 1.0f

#define MIN_X_AXIS_OF_ROTATION 0.0f
#define MAX_X_AXIS_OF_ROTATION 1.0f
#define MIN_Y_AXIS_OF_ROTATION 0.0f
#define MAX_Y_AXIS_OF_ROTATION 1.0f
#define MIN_Z_AXIS_OF_ROTATION 0.0f
#define MAX_Z_AXIS_OF_ROTATION 1.0f

#define MIN_SIZE 0.1f
#define MAX_SIZE 0.3f

#define MIN_TTL 10.0f
#define MAX_TTL 30.0f

class FireParticle
{
public:
	static GLfloat randBetween(GLfloat hi, GLfloat low);

	FireParticle(GLuint modelUniformLocation, MineCraftBlock *mcBlock, glm::vec3 location);

	void display();

	void init(GLuint positionAttribLocation, GLuint colorIntensityAttribLocation);

	void update();

	bool isDead();

	GLfloat getDistance(glm::vec3 startLocation);

	~FireParticle();

private:
	GLuint modelUniformLocation;
	
	MineCraftBlock *mcBlock;

	GLfloat velocity, rotationalVelocity;
	GLfloat angle;
	GLfloat size;
	GLfloat ttl;
	glm::vec3 direction, axisOfRotation;
	glm::vec3 location;
};