#pragma once

#include "glm/glm.hpp"

namespace Engine {
	class Camera {
	public: 
		enum class Movement {
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT,
			UP,
			DOWN
		};

		struct ClipPlanes {
			float near = 0.1f;
			float far = 1000.0f;
		};

		Camera(glm::vec2 viewport_size)
			:m_ViewportSize(viewport_size) {}
		Camera(glm::mat4 view, glm::mat4 projection, glm::vec2 viewport_size)
			:m_View(view), m_Projection(projection), m_ViewportSize(viewport_size) {}
		Camera(glm::vec3 position, glm::vec3 direction, glm::mat4 view, glm::mat4 projection, glm::vec2 viewport_size)
			:m_Position(position), m_Direction(direction), m_View(view), m_Projection(projection), m_ViewportSize(viewport_size) {}
		virtual ~Camera() = default;

		glm::mat4 getViewProjectionMatrix() 
		{
			return m_ViewProjection;
		}
		
		glm::mat4 getProjectionMatrix() {
			return m_Projection;
		}

		glm::mat4 getViewMatrix() {
			return m_View;
		}

		glm::vec3 getPosition() {
			return m_Position;
		}

		glm::vec3 getDirection() {
			return m_Direction;
		}

		void setViewportSize(uint32_t width, uint32_t height)
		{
			m_ViewportSize.x = width;
			m_ViewportSize.y = height;
		}

		virtual void unlock() = 0;
		virtual void lock() = 0;
		virtual void toggleLock() = 0;
	protected:
		glm::vec3 m_Position = glm::vec3(0.0f);
		glm::vec3 m_Direction = glm::vec3(1.0f, 0.0f, 0.0f);

		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
		glm::mat4 m_ViewProjection = glm::mat4(1.0f);

		glm::vec2 m_ViewportSize = glm::vec2(0.0f);
		ClipPlanes m_ClipPlanes = ClipPlanes();
	};
}