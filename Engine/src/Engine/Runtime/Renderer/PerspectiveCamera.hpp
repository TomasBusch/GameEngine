#pragma once
#include "Camera.hpp"
#include "glm/glm.hpp"
namespace Engine {

	class PerspectiveCamera : public Camera {
	private:

		//World Space
		glm::vec3 m_WorldUp;

		//Camera Space
		glm::vec3 m_CameraRight;
		glm::vec3 m_CameraUp;

		//Rotation
		glm::float32 m_Pitch;
		glm::float32 m_Yaw;
		glm::float32 m_Roll;

		//Look
		glm::float32 m_LookSensitivity;
		bool m_FirstLook;
		glm::float32 m_Zoom;

		bool m_Locked;

		//Movement
		uint32_t m_MovSpeed;


	public:
		PerspectiveCamera(uint32_t width, uint32_t height);

		void move(Camera::Movement direction, float delta_time);
		void look(double xpos, double ypos, bool constrain_pitch);
		void zoom(double offset);

		virtual void unlock() override;
		virtual void lock() override;
		virtual void toggleLock() override;

	private:
		void updateViewMatrix();
		void updateProjectionMatrix();
		void updateViewProjectionMatrix();
		void updateCameraVectors();
	};
}