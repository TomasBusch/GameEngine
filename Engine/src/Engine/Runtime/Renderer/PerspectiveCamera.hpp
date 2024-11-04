#pragma once
#include "Camera.hpp"
#include "glm/glm.hpp"
namespace Engine {

	class PerspectiveCamera : public Camera {
	private:
		glm::vec3 m_Position;
		glm::vec3 m_Direction;
		//glm::vec3 m_Target;

		//World Space
		glm::vec3 m_WorldUp;

		//Camera Space
		glm::vec3 m_CameraRight;
		glm::vec3 m_CameraUp;

		//Rotation
		glm::float32 m_Pitch;
		glm::float32 m_Yaw;
		glm::float32 m_Roll;

		//glm::mat4 m_ViewMatrix;

		//Look
		glm::float32 m_LookSensitivity;
		bool m_FirstLook;
		uint32_t m_ViewportWidth;
		uint32_t m_ViewportHeight;
		glm::float32 m_Zoom;

		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_MVPMatrix;

		bool m_Locked;

		//Movement
		uint32_t m_MovSpeed;


	public:
		PerspectiveCamera(uint32_t width, uint32_t height);

		virtual glm::mat4 getViewProjectionMatrix() override {
			return m_MVPMatrix;
		}

		virtual glm::mat4 getProjectionMatrix() override {
			return m_ProjectionMatrix;
		}

		virtual glm::mat4 getViewMatrix() override {
			return m_ViewMatrix;
		}

		virtual glm::vec3 getPosition() override {
			return m_Position;
		}

		virtual glm::vec3 getDirection() override {
			return m_Direction;
		}

		virtual void setViewportSize(uint32_t width, uint32_t height) override;

		void move(Camera::Movement direction, float delta_time);
		void look(double xpos, double ypos, bool constrain_pitch);
		void zoom(double offset);

		virtual void unlock() override;
		virtual void lock() override;
		virtual void toggleLock() override;

	private:
		void updateViewMatrix();
		void updateProjectionMatrix();
		void updateMVPMatrix();
		void updateCameraVectors();
	};
}