#include "Mesh.h"

//Getters and setters
GLuint Mesh::getVertexArrayObject() { return this->vertexArrayObject; }
GLuint* Mesh::getVertexArrayBuffers() { return this->vertexArrayBuffers; }
unsigned int Mesh::getNumVertices() { return this->numVertices; }
void Mesh::setNumVertices(unsigned int numVertices) { this->numVertices = numVertices; }

void Mesh::init(Vertex* vertices)
{
	//Generate vertex arrays
	//NOTE: Would run a get function here, but since I need the address of my VAO I chose not to
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(getVertexArrayObject());

	//Generate & bind vertex array buffers, send data
	glGenBuffers(1, getVertexArrayBuffers());
	glBindBuffer(GL_ARRAY_BUFFER, getVertexArrayBuffers()[0]);
	glBufferData(GL_ARRAY_BUFFER, getNumVertices() * sizeof(vertices[0]), vertices, GL_STATIC_DRAW);

	//Tell OpenGL how to interpret our data
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	//Unbind vertex arrays
	glBindVertexArray(0);
}

void Mesh::draw()
{
	//Re-bind vertex array
	glBindVertexArray(getVertexArrayObject());

	//Draw array data to screen
	glDrawArrays(GL_TRIANGLES, 0, getNumVertices());

	//Unbind again
	glBindVertexArray(0);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	//Set properties given input
	setNumVertices(numVertices);

	//Initialize mesh
	init(vertices);
}

Mesh::~Mesh()
{
	//Delete vertex arrays
	glDeleteVertexArrays(1, &vertexArrayObject);
}