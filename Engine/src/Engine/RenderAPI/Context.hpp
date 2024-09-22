#pragma once

#include "Engine/Core/Base.hpp"

#include "RenderAPI.hpp"

namespace Engine::RenderAPI {

	class Context {
	public:
		Context() = default;
		virtual ~Context() = default;

		virtual void Init() = 0;

		static Scope<Context> Create(RenderAPITypes type);
	};

}
