#include "Mesh2.h"

// instanciate default mesh for testing purposes
Mesh2::Mesh2()
{
	numOfVertices = 3;
	numOfIndices = 3;

	// default vertices
	vertices = new glm::vec4[numOfVertices] {
		glm::vec4(-0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -1.5f, 1.0f)
	};

	// default color intencities
	colorIntencities = new glm::vec4[numOfVertices] {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
	};

	indices = new GLuint[3] {
		0, 1, 2
	};
}

Mesh2::Mesh2(glm::vec4 *vertices, glm::vec4 *colorIntencities, GLuint numOfVertices, GLuint *indices, GLuint numOfIndices)
{
	this->vertices = vertices;
	this->colorIntencities = colorIntencities;
	this->numOfVertices = numOfVertices;

	this->indices = indices;
	this->numOfIndices = numOfIndices;
}

// initialize the mesh (VAO, IBO, VBO)
void Mesh2::init(GLuint positionAttribLocation, GLuint colorIntencityAttribLocation)
{
	this->numOfVertices = numOfVertices;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices + sizeof(colorIntencities[0]) * numOfVertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0]) * numOfVertices, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, sizeof(colorIntencities[0]) * numOfVertices, colorIntencities);

	// IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

	// attributing vertices to shader
	glEnableVertexAttribArray(positionAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// attributing colors to shader
	glEnableVertexAttribArray(colorIntencityAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(colorIntencityAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices[0]) * numOfVertices));

	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// display the mesh
void Mesh2::display()
{
	// bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// draw
	glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);

	// unbind
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

// delete the mesh
Mesh2::~Mesh2()
{
}
