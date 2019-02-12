#include "MineCraftBlock.h"

MineCraftBlock::MineCraftBlock(GLuint modelUniformLocation)
{
	this->modelUniformLocation = modelUniformLocation;

	GLuint numOfVertices = 25;
	glm::vec4 *vertices = new glm::vec4[numOfVertices]{
		glm::vec4(-0.5f, 0.0f, 0.5f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.5f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.5f, 1.0f),

		glm::vec4(-0.5f, 0.0f, 0.25f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.25f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.25f, 1.0f),

		glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f),
		glm::vec4(-0.25f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.25f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.0f, 1.0f),

		glm::vec4(-0.5f, 0.0f, -0.25f, 1.0f),
		glm::vec4(-0.25f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.0f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.25f, 0.0f, -0.25f, 1.0f),
		glm::vec4(0.5f, 0.0f, -0.25f, 1.0f),

		glm::vec4(-0.5f, 0.0f, -0.5f, 1.0f),
		glm::vec4(-0.25f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.25f, 0.0f, -0.5f, 1.0f),
		glm::vec4(0.5f, 0.0f, -0.5f, 1.0f),
	};

	glm::vec4 *colorIntensities = new glm::vec4[numOfVertices]{
		glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
		glm::vec4(0.3f, 0.3f, 0.3f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),

		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
		glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),

		glm::vec4(0.3f, 0.3f, 0.3f, 1.0f),
		glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),

		glm::vec4(0.1f, 0.1f, 0.1f, 1.0f),
		glm::vec4(0.3f, 0.3f, 0.3f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.3f, 0.3f, 0.3f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),

		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
	};

	GLuint numOfIndices = 6 * 16;
	GLuint *indices = new GLuint[numOfIndices]{
		1, 6, 0, 6, 5, 0,
		2, 7, 1, 7, 6, 1,
		3, 8, 2, 8, 7, 2,
		4, 9, 3, 9, 8, 3,

		6, 11, 5, 11, 10, 5,
		7, 12, 6, 12, 11, 6,
		8, 13, 7, 13, 12, 7,
		9, 14, 8, 14, 13, 8,

		11, 16, 10, 16, 15, 10,
		12, 17, 11, 17, 16, 11,
		13, 18, 12, 18, 17, 12,
		14, 19, 13, 19, 18, 13,

		16, 21, 15, 21, 20, 15,
		17, 22, 16, 22, 21, 16,
		18, 23, 17, 23, 22, 17,
		19, 24, 18, 24, 23, 18,
	};

	faceMesh = new Mesh2(vertices, colorIntensities, numOfVertices, indices, numOfIndices);
}

// display the block (use startModel as the starting matrix for model transformations)
void MineCraftBlock::display(glm::mat4 startModel)
{
	glm::mat4 model;
	
	// front
	model = glm::translate(startModel, glm::vec3(0.0f, 0.0f, 0.5f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();

	// back
	model = glm::translate(startModel, glm::vec3(0.0f, 0.0f, -0.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();

	// top
	model = glm::translate(startModel, glm::vec3(0.0f, 0.5f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();

	// bottom
	model = glm::translate(startModel, glm::vec3(0.0f, -0.5f, 0.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();

	// left
	model = glm::translate(startModel, glm::vec3(-0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();

	// right
	model = glm::translate(startModel, glm::vec3(0.5f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(modelUniformLocation, 1, GL_FALSE, glm::value_ptr(model));
	faceMesh->display();
}

// display the model and use a unit matrix for model transformations
void MineCraftBlock::display()
{
	display(glm::mat4());
}

// initialize the block
void MineCraftBlock::init(GLuint positionAttribLocation, GLuint colorIntencityAttribLocation)
{
	faceMesh->init(positionAttribLocation, colorIntencityAttribLocation);
}

// delete the block
MineCraftBlock::~MineCraftBlock()
{
	delete faceMesh;
}
