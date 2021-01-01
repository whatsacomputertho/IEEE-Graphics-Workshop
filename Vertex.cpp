#include "Vertex.h"
#include <glm.hpp>

//Getter and setter
glm::vec3 Vertex::getPosition() { return this->position; }
void Vertex::setPosition(glm::vec3 position) { this->position = position; }

//Constructor
Vertex::Vertex(glm::vec3 position) 
{
	//Set position attribute given vec3 input
	setPosition(position);
}

//Destructor
Vertex::~Vertex()
{
	//do nothing for now
}