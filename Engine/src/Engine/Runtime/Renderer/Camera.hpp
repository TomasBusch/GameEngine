#pragma once

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

		virtual glm::mat4 getViewProjectionMatrix() = 0;
		virtual glm::mat4 getProjectionMatrix() = 0;
		virtual glm::mat4 getViewMatrix() = 0;

		virtual glm::vec3 getPosition() = 0;
		virtual glm::vec3 getDirection() = 0;

		virtual void setViewportSize(uint32_t width, uint32_t height) = 0;

		virtual void unlock() = 0;
		virtual void lock() = 0;
		virtual void toggleLock() = 0;
	};
}