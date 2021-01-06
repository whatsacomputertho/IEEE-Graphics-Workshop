#include "Camera.h"
#include "glm.hpp"
#include <stdio.h>

//Getters and setters
glm::mat4 Camera::getPerspective() { return this->perspective; }
glm::vec3 Camera::getPosition() { return this->position; }
glm::vec3 Camera::getForward() { return this->forward; }
glm::vec3 Camera::getUpward() { return this->upward; }
void Camera::setPerspective(glm::mat4 perspective) { this->perspective = perspective; }
void Camera::setPosition(glm::vec3 position) { this->position = position; }
void Camera::setForward(glm::vec3 forward) { this->forward = forward; }
void Camera::setUpward(glm::vec3 upward) { this->upward = upward; }

glm::mat4 Camera::getViewProjection()
{
	//Combine perspective matrix with an additional world rotation matrix
	return getPerspective() * glm::lookAt(getPosition(), getPosition() + getForward(), getUpward());
}

void Camera::updatePosition(int direction)
{
	float threshold = 0.05f;

	glm::vec3 cProduct;

	switch (direction)
	{
	case 0:
		setPosition(glm::vec3(getPosition().x + (getForward().x * threshold), getPosition().y + (getForward().y * threshold), getPosition().z + (getForward().z * threshold)));
		break;
	case 1:
		//Get cross product of forward and up vector
		cProduct = glm::cross(getForward(), getUpward());
		setPosition(glm::vec3(getPosition().x - (cProduct.x * threshold), getPosition().y - (cProduct.y * threshold), getPosition().z - (cProduct.z * threshold)));
		break;
	case 2:
		setPosition(glm::vec3(getPosition().x - (getForward().x * threshold), getPosition().y - (getForward().y * threshold), getPosition().z - (getForward().z * threshold)));
		break;
	case 3:
		//Get cross product of forward and up vector
		cProduct = glm::cross(getForward(), getUpward());
		setPosition(glm::vec3(getPosition().x + (cProduct.x * threshold), getPosition().y + (cProduct.y * threshold), getPosition().z + (cProduct.z * threshold)));
		break;
	}
}

void Camera::updateRotation(int xMouse, int yMouse, int width, int height)
{
	//Calculate updated forward and up vectors using mouse coords & window dimensions
	float forwardXCoord = sinf(-1.0f * (((float)xMouse - ((float)width / 2.0f)) / ((float)width / 2.0f)) * (sqrt(3) / 2.0f));
	float forwardZCoord = cosf(-1.0f * (((float)xMouse - ((float)width / 2.0f)) / ((float)width / 2.0f)) * (sqrt(3) / 2.0f));
	float upwardYCoord = cosf((((float)yMouse - ((float)height / 2.0f)) / ((float)height / 2.0f)) * (sqrt(3) / 2.0f));
	float upwardZCoord = sinf((((float)yMouse - ((float)height / 2.0f)) / ((float)height / 2.0f)) * (sqrt(3) / 2.0f));

	//Update the respective coords in the forward and up vectors stored in our camera object
	setForward(glm::vec3(forwardXCoord, 0.0f - upwardZCoord, forwardZCoord));
	setUpward(glm::vec3(0.0f, upwardYCoord, upwardZCoord));
}

Camera::Camera(glm::vec3 position, float fieldOfView, float aspectRatio, float zNear, float zFar)
{
	//Set perspective matrix and position vector using input, generate default forward and up vectors
	setPerspective(glm::perspective(fieldOfView, aspectRatio, zNear, zFar));
	setPosition(position);
	setForward(glm::vec3(0.0f, 0.0f, 1.0f));
	setUpward(glm::vec3(0.0f, 1.0f, 0.0f));
}

Camera::~Camera()
{
	//do nothing for now
}