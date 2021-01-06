#pragma once
#include <glm.hpp>
#include <gtx/transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, float fieldOfView, float aspectRatio, float zNear, float zFar);
	~Camera();
	void updateRotation(int xMouse, int yMouse, int width, int height);
	void updatePosition(int direction);
	glm::mat4 getViewProjection();
	glm::mat4 getPerspective();
	glm::vec3 getPosition();
	glm::vec3 getForward();
	glm::vec3 getUpward();
	void setPerspective(glm::mat4 perspective);
	void setPosition(glm::vec3 position);
	void setForward(glm::vec3 forward);
	void setUpward(glm::vec3 upward);

private:
	glm::mat4 perspective;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 upward;
};