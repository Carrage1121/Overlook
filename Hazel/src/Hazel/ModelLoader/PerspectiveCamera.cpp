#include "hzpch.h"
#include "PerspectiveCamera.h"

namespace Hazel
{
	// constructor with vectors
	PerspectiveCamera::PerspectiveCamera(glm::vec3 position, unsigned int width, unsigned int height, glm::vec3 up, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), Front(glm::vec3(0.0f, 0.0f, -1.0f))
	{
		m_Position = position;
		WorldUp = up;
		Yaw = yaw;
		Pitch = pitch;
		WindowsResize(width, height);
	}
	// constructor with scalar values
	PerspectiveCamera::PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		m_Position = glm::vec3(posX, posY, posZ);
		WorldUp = glm::vec3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	void PerspectiveCamera::ProcessKeyboard(Camera_Movement direction)
	{
		float velocity = 0.1f;
		if (direction == FORWARD)
			m_Position += Front * velocity;
		if (direction == BACKWARD)
			m_Position -= Front * velocity;
		if (direction == LEFT)
			m_Position += Right * velocity;
		if (direction == RIGHT)
			m_Position -= Right * velocity;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::ProcessMouseScroll(float yoffset)
	{
		Zoom -= (float)yoffset;
		if (Zoom < 1.0f)
			Zoom = 1.0f;
		if (Zoom > 45.0f)
			Zoom = 45.0f;
	}

	void PerspectiveCamera::WindowsResize(unsigned int	width, unsigned int	height)
	{
		this->width = width;
		this->height = height;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetRotation(float rotationX, float rotationY)
	{
		Pitch += rotationY;
		Yaw += rotationX;

		std::fmodf(PITCH, 360);
		std::fmodf(Yaw, 360);
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
//  	glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
//  		(glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationY), glm::vec3(0, 1, 0)) *
//  			glm::rotate(glm::mat4(1.0f), glm::radians(m_RotationX), glm::vec3(1, 0, 0)));

//   		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::eulerAngleXYZ(glm::radians(m_RotationX), glm::radians(m_RotationY), 0.f);
//  		m_ViewMatrix = glm::inverse(transform);
		updateCameraVectors();
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + Front, Up);
		m_ProjectionMatrix = glm::perspective(glm::radians(this->Zoom), (float)width / (float)height, 0.1f, 100.0f);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	// calculates the front vector from the Camera's (updated) Euler Angles
	void PerspectiveCamera::updateCameraVectors()
	{
		// calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);
		// also re-calculate the Right and Up vector
		Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = glm::normalize(glm::cross(Right, Front));
	}
}