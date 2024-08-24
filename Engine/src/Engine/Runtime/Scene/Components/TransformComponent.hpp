#pragma once

#include <glm/glm.hpp>

namespace Engine::Components {

	struct TransformComponent {
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4 transform)
			: Transform(transform) {};
		operator glm::mat4& () { return Transform; };
		operator const glm::mat4& () const { return Transform; };
	};
}