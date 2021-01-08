#pragma once
#include "Vertex.h"
#include <glm.hpp>
#include <glew.h>

class Mesh
{
private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObjects[1];
	unsigned int numVertices;
	void init(Vertex* vertices);

public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	~Mesh();
	void draw();
	GLuint getVertexArrayObject();
	GLuint* getVertexBufferObjects();
	unsigned int getNumVertices();
	void setNumVertices(unsigned int numVertices);
};

