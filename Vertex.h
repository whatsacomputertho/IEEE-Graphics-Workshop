#pragma once
#include <glm.hpp>

class Vertex
{
private:
	glm::vec3 position;

public:
	Vertex(glm::vec3 position);
	~Vertex();
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
};

