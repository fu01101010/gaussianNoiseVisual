#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class cameraDirection {

	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class camera {

public:
	static camera defaultCamera;

	glm::vec3 cameraPosition;

	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;

	glm::vec3 worldUp;

	float yaw; //крен
	float pitch; //тангаж

	float speed;
	float sensetivity;

	float zoom;

	camera(glm::vec3 position);
	
	void updateCameraDirection(double _dx, double _dy);
	void updateCameraPosition(cameraDirection direction, double _dt);
	void updateCameraZoom(double _dy);

	float getZoom();

	glm::mat4 getViewMatrix();

private:

	void updateCameraVectors();
};

#endif
