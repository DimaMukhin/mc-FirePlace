#include "BlockMeshFactory.h"

namespace block {
	GLuint numOfVertices = 36;

	glm::vec4 *vertices = new glm::vec4[numOfVertices] {
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),	// a
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),		// b
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),		// c
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),		// d
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),	// a'
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),	// b'
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),		// c'
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),	// d'
	};

	glm::vec4 *colors = new glm::vec4[numOfVertices] {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f) // red
	};

	int vertexIndices[] = {
		0, 1, 2, 2, 3, 0, // front
		4, 5, 6, 6, 7, 4, // back
		3, 2, 6, 6, 7, 3, // top
		0, 1, 5, 5, 4, 0, // bottom
		0, 4, 7, 7, 3, 0, // left
		1, 5, 6, 6, 2, 1, // right
	};

	int colorIndices[] = {
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
		0,0,0,0,0,0,
	};

	glm::vec4 * generateColors(int * colors, int numOfColors)
	{
		glm::vec4 *generatedColors = new glm::vec4[numOfColors];

		for (int i = 0; i < numOfColors; i++)
		{

			generatedColors[i] = block::colors[colors[i]];
		}

		return generatedColors;
	}

	glm::vec4 * generateVertices(int * vertices, int numOfVertices)
	{
		glm::vec4 *generatedVertices = new glm::vec4[numOfVertices];

		for (int i = 0; i < numOfVertices; i++)
		{

			generatedVertices[i] = block::vertices[vertices[i]];
		}

		return generatedVertices;
	}

	Mesh* createBlockMesh()
	{
		glm::vec4 *vertices = generateVertices(vertexIndices, numOfVertices);
		glm::vec4 *colors = generateColors(colorIndices, numOfVertices);
		return new Mesh(vertices, colors, numOfVertices);
	}
}
