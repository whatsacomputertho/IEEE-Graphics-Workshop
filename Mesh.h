#pragma once
#include "Vertex.h"
#include <glm.hpp>
#include <glew.h>

class Mesh
{
private:
	GLuint vertexArrayObject;
	GLuint vertexArrayBuffers[1];
	unsigned int numVertices;
	void init(Vertex* vertices);

public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void draw();
	GLuint getVertexArrayObject();
	GLuint* getVertexArrayBuffers();
	unsigned int getNumVertices();
	void setNumVertices(unsigned int numVertices);
};

