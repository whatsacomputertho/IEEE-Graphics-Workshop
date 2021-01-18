#include "Camera.h"
#include "glm.hpp"
#include <iostream>
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
	/*
		Write code here!
	*/
}

void Camera::updateRotation(int xMouse, int yMouse, int width, int height)
{
	/*
		Write code here!s
	*/
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