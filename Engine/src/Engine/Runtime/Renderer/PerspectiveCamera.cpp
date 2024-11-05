#include "PerspectiveCamera.hpp"

#include "glm/gtc/matrix_transform.hpp"
namespace Engine {

	PerspectiveCamera::PerspectiveCamera(uint32_t width, uint32_t height)
		:Camera(glm::vec2(width, height))
		, m_WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)), m_Yaw(-90.0f), m_Pitch(0.0f), m_Roll(0.0f)
		, m_FirstLook(true), m_LookSensitivity(0.5f), m_Zoom(45.0f),
		m_Locked(false),
		m_MovSpeed(10)
	{
		m_CameraRight = glm::normalize(glm::cross(m_WorldUp, m_Direction));
		m_CameraUp = glm::cross(m_Direction, m_CameraRight);

		m_Projection = glm::perspective(
			glm::radians(m_Zoom), 
			(float)m_ViewportSize.x / (float)m_ViewportSize.y, 
			m_ClipPlanes.near,
			m_ClipPlanes.far
		);

		m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_CameraUp);
		m_ViewProjection = m_Projection * m_View;

		updateViewMatrix();
		updateProjectionMatrix();
		updateViewProjectionMatrix();
		updateCameraVectors();
	}

	void PerspectiveCamera::updateViewMatrix() {
		m_View = glm::lookAt(m_Position, m_Position + m_Direction, m_CameraUp);
	}

	void PerspectiveCamera::updateProjectionMatrix() {
		m_Projection = glm::perspective(glm::radians(m_Zoom), (float)m_ViewportSize.x / (float)m_ViewportSize.y, 0.1f, 10000.0f);
	}

	void PerspectiveCamera::updateViewProjectionMatrix() {
		m_ViewProjection = m_Projection * m_View;
	}

	void PerspectiveCamera::updateCameraVectors() {
		glm::vec3 direction;
		direction.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		direction.y = sin(glm::radians(m_Pitch));
		direction.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Direction = glm::normalize(direction);

		m_CameraRight = glm::normalize(glm::cross(m_Direction, m_WorldUp));
		m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_Direction));
	}

	void PerspectiveCamera::move(Camera::Movement movement, float deltaTime) {
		if (!m_Locked) {

			//float velocity = MovementSpeed * deltaTime;
			float velocity = m_MovSpeed * deltaTime;
			if (movement == Camera::Movement::FORWARD)
				m_Position += m_Direction * velocity;
			if (movement == Camera::Movement::BACKWARD)
				m_Position -= m_Direction * velocity;
			if (movement == Camera::Movement::LEFT)
				m_Position -= m_CameraRight * velocity;
			if (movement == Camera::Movement::RIGHT)
				m_Position += m_CameraRight * velocity;
			if (movement == Camera::Movement::UP)
				m_Position += m_WorldUp * velocity;
			if (movement == Camera::Movement::DOWN)
				m_Position -= m_WorldUp * velocity;

			updateViewMatrix();
			updateViewProjectionMatrix();
		}
	}

	void PerspectiveCamera::look(double xposIn, double yposIn, bool constrain_pitch = true) {
		if (!m_Locked) {

			float xpos = static_cast<float>(xposIn);
			float ypos = static_cast<float>(yposIn);

			float xoffset = xpos - m_ViewportSize.x / 2;
			float yoffset = (m_ViewportSize.y / 2) - ypos; // reversed since y-coordinates go from bottom to top

			//Avoids jump in first move
			if (m_FirstLook) {
				m_FirstLook = false;
			}
			else {
				xoffset *= m_LookSensitivity;
				yoffset *= m_LookSensitivity;

				m_Yaw += xoffset;
				m_Pitch += yoffset;

				// make sure that when pitch is out of bounds, screen doesn't get flipped
				if (constrain_pitch)
				{
					if (m_Pitch > 89.0f)
						m_Pitch = 89.0f;
					if (m_Pitch < -89.0f)
						m_Pitch = -89.0f;
				}

				// update Front, Right and Up Vectors using the updated Euler angles
				updateCameraVectors();
				updateViewMatrix();
				updateViewProjectionMatrix();
			}
		}
	}

	void PerspectiveCamera::zoom(double yoffset) {
		if (!m_Locked) {
			m_Zoom -= (float)yoffset * 10;
			if (m_Zoom < 1.0f)
				m_Zoom = 1.0f;
			if (m_Zoom > 45.0f)
				m_Zoom = 45.0f;

			updateProjectionMatrix();
			updateViewProjectionMatrix();
		}
	}

	void PerspectiveCamera::unlock() {
		m_Locked = false;
	}

	void PerspectiveCamera::lock() {
		m_Locked = true;
		m_FirstLook = true;
	}

	void PerspectiveCamera::toggleLock() {
		if (!m_Locked) {
			lock();
		}
		else {
			unlock();
		}
	}

}