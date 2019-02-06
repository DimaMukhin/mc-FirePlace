#pragma once

#include "common.h"
#include "Mesh2.h"

#include <glm/gtc/type_ptr.hpp>

class MineCraftBlock
{
public:
	MineCraftBlock(GLuint modelUniformLocation);

	void display(glm::mat4 startModel);

	void display();

	void init(GLuint positionAttribLocation, GLuint colorIntencityAttribLocation);

	~MineCraftBlock();

private:
	Mesh2 *faceMesh;
	GLuint modelUniformLocation;
};