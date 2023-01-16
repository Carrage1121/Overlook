#include "hzpch.h"
#include "camera.h"

namespace Hazel
{
	// constructor with vectors
	Camera::Camera(glm::vec3 position, unsigned int width, unsigned int height) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		m_Position = position;
		WindowsResize(width, height);
	}
	// constructor with scalar values
	Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		m_Position = glm::vec3(posX, posY, posZ);
		// 		WorldUp = glm::vec3(upX, upY, upZ);
		// 		Yaw = yaw;
		// 		Pitch = pitch;
		// 		updateCameraVectors();
	}

	void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		// 		float velocity = MovementSpeed * deltaTime;
		// 		if (direction == FORWARD)
		// 			Position += Front * velocity;
		// 		if (direction == BACKWARD)
		// 			Position -= Front * velocity;
		// 		if (direction == LEFT)
		// 			Position -= Right * velocity;
		// 		if (direction == RIGHT)
		// 			Position += Right * velocity;
	}

	void Camera::ProcessMouseMovement(float xoffset, float yoffset, unsigned char constrainPitch)
	{
		// 		xoffset *= MouseSensitivity;
		// 		yoffset *= MouseSensitivity;
		// 
		// 		Yaw += xoffset;
		// 		Pitch += yoffset;

				// make sure that when pitch is out of bounds, screen doesn't get flipped
		// 		if (constrainPitch)
		// 		{
		// 			if (Pitch > 89.0f)
		// 				Pitch = 89.0f;
		// 			if (Pitch < -89.0f)
		// 				Pitch = -89.0f;
		// 		}

				// update Front, Right and Up Vectors using the updated Euler angles
				//updateCameraVectors();
	}

	void Camera::ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

	void Camera::WindowsResize(unsigned int	width, unsigned int	height)
	{
		this->width = width;
		this->height = height;
		RecalculateViewMatrix();
	}


	void Camera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			(glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationY), glm::vec3(0, 1, 0)) +
				glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationX), glm::vec3(1, 0, 0)));

		m_ViewMatrix = glm::inverse(transform);

		m_ProjectionMatrix = glm::perspective(glm::radians(this->Zoom), (float)width / (float)height, 0.1f, 100.0f);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}