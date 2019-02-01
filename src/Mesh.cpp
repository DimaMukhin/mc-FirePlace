#include "Mesh.h"

Mesh::Mesh()
{
	numOfVertices = 3;

	// default vertices
	vertices = new glm::vec4[numOfVertices] {
		glm::vec4(-0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, -0.5f, -1.5f, 1.0f),
		glm::vec4(0.5f, 0.5f, -1.5f, 1.0f)
	};

	// default colors
	colors = new glm::vec4[numOfVertices] {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
	};
}

Mesh::Mesh(glm::vec4 * vertices, glm::vec4 * colors, GLuint numOfVertices)
{
	this->vertices = vertices;
	this->colors = colors;
	this->numOfVertices = numOfVertices;
}

void Mesh::init(GLuint positionAttribLocation, GLuint colorAttribLocation)
{
	this->numOfVertices = numOfVertices;

	// VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices + sizeof(colors[0]) * numOfVertices, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices[0]) * numOfVertices, vertices);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, sizeof(colors[0]) * numOfVertices, colors);

	// attributing vertices to shader
	glEnableVertexAttribArray(positionAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(positionAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	// attributing colors to shader
	glEnableVertexAttribArray(colorAttribLocation); // must be enabled after VAO and VBO
	glVertexAttribPointer(colorAttribLocation, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(vertices[0]) * numOfVertices));

	// unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::display()
{
	// bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// draw
	glDrawArrays(GL_TRIANGLES, 0, numOfVertices);

	// unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	delete vertices;
	delete colors;
}
