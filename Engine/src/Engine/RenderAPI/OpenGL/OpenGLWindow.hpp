#pragma once

#include "Engine/Runtime/Window.hpp"

namespace Engine {
	class OpenGLWindow : public Window {
	public:
		OpenGLWindow(Window::Params& params);
		virtual ~OpenGLWindow();

		virtual void Init() override;
		virtual void OnUpdate() override;
		virtual void Shutdown() override;
		virtual bool ShouldClose() override;

		virtual void SetWindowGrabInput(bool grab) override;

		virtual void* getNativeHandle() override;
	};
}