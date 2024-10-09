#include "camera.h"

camera::camera(glm::vec3 position) :
	cameraPosition(position),
	worldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	yaw(0.0f),
	pitch(0.0f),
	speed(2.5f),
	zoom(45.0f),
	cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)) {

	updateCameraVectors();
}

void camera::updateCameraDirection(double _dx, double _dy) {

	yaw += _dx;
	pitch += _dy;

	if (pitch > 89.9f) {

		pitch = 89.9f;
	}
	else if (pitch < -89.9f) {

		pitch = -89.9f;
	}

	updateCameraVectors();
};

void camera::updateCameraPosition(cameraDirection direction, double _dt) {

	float velocity = (float)_dt * speed;

	switch (direction) {

		case (cameraDirection::FORWARD): {

			cameraPosition += cameraFront * velocity;
			break;
		}
		case cameraDirection::BACKWARD: {

			cameraPosition -= cameraFront * velocity;
			break;
		}
		case cameraDirection::RIGHT: {

			cameraPosition += cameraRight * velocity;
			break;
		}
		case cameraDirection::LEFT: {

			cameraPosition -= cameraRight * velocity;
			break;
		}
		case cameraDirection::UP: {

			//cameraPosition += cameraUp * velocity;
			cameraPosition += worldUp * velocity;
			break;
		}
		case cameraDirection::DOWN: {

			//cameraPosition -= cameraUp * velocity;
			cameraPosition -= worldUp * velocity;
			break;
		}
		
		case cameraDirection::NONE: {
			
			break;
		}
	}
};

void camera::updateCameraZoom(double _dy) {

	if (zoom >= 7.0f && zoom <= 45.0f) {

		zoom -= _dy;
	}
	else if (zoom < 7.0f) {

		zoom = 7.0f;
	}
	else {

		zoom = 45.0f;
	}
};

float camera::getZoom() {

	return zoom;
}

glm::mat4 camera::getViewMatrix() {

	//return glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
	return glm::lookAt(cameraPosition, glm::vec3(0.0f), cameraUp);

};

void camera::updateCameraVectors() {

	glm::vec3 direction;

	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	cameraFront = glm::normalize(direction);
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
