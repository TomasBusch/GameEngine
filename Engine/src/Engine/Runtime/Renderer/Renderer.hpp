#pragma once

#include "Engine/Runtime/Scene/Scene.hpp"

namespace Engine {
	class Renderer {
		Renderer();
		~Renderer() = default;

		void Draw(Scene& scene);

	};
}