#pragma once

#include "Platform/Window.h"

namespace Engine {
	class ImguiContext {
	public:
		ImguiContext() = default;

		virtual void Render() = 0;
	};
}