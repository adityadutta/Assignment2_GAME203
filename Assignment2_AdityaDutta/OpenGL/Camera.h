#ifndef CAMERA_H
#define CAMERA_H

#include<vector>

#define GLEW_STATIC
#include<GL\glew.h>

#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>

namespace CAMERA {
	enum Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};
}
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 2.5f;
const GLfloat SENSITIVITY = 0.1f;
const GLfloat ZOOM = 45.0f;

class Camera {
private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat movementSpeed;
	GLfloat mouseSensitivity;
	GLfloat zoom;

	void updateCameraVectors() {
		glm::vec3 _front;
		_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		_front.y = sin(glm::radians(pitch));
		_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(_front);
		// Also re-calculate the Right and Up vector
		right = glm::normalize(glm::cross(front, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		up = glm::normalize(glm::cross(right, front));
	}

public:
	Camera(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat _yaw = YAW, GLfloat _pitch = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
		position = _position;
		worldUp = _up;
		yaw = _yaw;
		pitch = _pitch;
		updateCameraVectors();
	}

	Camera(GLfloat _posX, GLfloat _posY, GLfloat _posZ, GLfloat _upX, GLfloat _upY, GLfloat _upZ, GLfloat _yaw, GLfloat _pitch) : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED), mouseSensitivity(SENSITIVITY), zoom(ZOOM) {
		position = glm::vec3(_posX, _posY, _posZ);
		worldUp = glm::vec3(_upX, _upY, _upZ);
		yaw = _yaw;
		pitch = _pitch;
		updateCameraVectors();
	}

	glm::mat4 GetViewMatrix() {
		return glm::lookAt(position, position + front, up);
	}

	glm::vec3 GetPosition() {
		return position;
	}

	glm::vec3 GetFront() {
		return front;
	}

	// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	void ProcessKeyboard(CAMERA::Camera_Movement _direction, float _deltaTime)
	{
		float velocity = movementSpeed * _deltaTime;
		if (_direction == CAMERA::FORWARD)
			position += front * velocity;
		if (_direction == CAMERA::BACKWARD)
			position -= front * velocity;
		if (_direction == CAMERA::LEFT)
			position -= right * velocity;
		if (_direction == CAMERA::RIGHT)
			position += right * velocity;
	}

	void ProcessMouseMovement(GLfloat _xOffset, GLfloat _yOffset, GLboolean constrainPitch = true) {
		_xOffset *= mouseSensitivity;
		_yOffset *= mouseSensitivity;

		yaw += _xOffset;
		pitch += _yOffset;

		if (constrainPitch) {
			if (pitch > 89.0f) {
				pitch = 89.0f;
			}
			if (pitch < -89.0f) {
				pitch = -89.0f;
			}
		}

		updateCameraVectors();
	}

	void ProcessMouseScroll(GLfloat _yOffset) {
		if (zoom >= 1.0f && zoom <= 45.0f) {
			zoom -= _yOffset;
		}

		if (zoom <= 1.0f) {
			zoom = 1.0f;
		}

		if (zoom >= 45.0f) {
			zoom = 45.0f;
		}
	}

	GLfloat GetZoom() {
		return glm::radians(zoom);
	}
};

#endif // !CAMERA_H

