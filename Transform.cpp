#include "Transform.h"
#include <glm.hpp>
#include <gtx/transform.hpp>

glm::vec3 Transform::getPosition() { return this->position; }
glm::vec3 Transform::getRotation() { return this->rotation; }
glm::vec3 Transform::getScale() { return this->scale; }
void Transform::setPosition(glm::vec3 position) { this->position = position; }
void Transform::setRotation(glm::vec3 rotation) { this->rotation = rotation; }
void Transform::setScale(glm::vec3 scale) { this->scale = scale; }

glm::mat4 Transform::getWorld()
{
	//Get translation, rotation, and scalar matrices using information from our vectors
	glm::mat4 positionMatrix = glm::translate(getPosition());
	glm::mat4 xRotationMatrix = glm::rotate(getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 yRotationMatrix = glm::rotate(getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 zRotationMatrix = glm::rotate(getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleMatrix = glm::scale(getScale());

	//Combine into one matrix
	glm::mat4 worldMatrix = zRotationMatrix * yRotationMatrix * xRotationMatrix * positionMatrix * scaleMatrix;

	//Return all matrices combined into one
	return worldMatrix;
}

Transform::Transform()
{
	//Set default position, rotation, and scalar vectors
	setPosition(glm::vec3());
	setRotation(glm::vec3());
	setScale(glm::vec3(1.0f, 1.0f, 1.0f));
}

Transform::~Transform() 
{
	//do nothing for now
}