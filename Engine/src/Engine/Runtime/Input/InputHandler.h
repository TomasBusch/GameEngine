#pragma once
#include "pch.h"
#include "Engine/Core/Base.h"


#include "Platform/OpenGL/OpenGLWindow.h"

#include "Engine/Core/Events/InputEvents.h"
#include "Engine/Core/Events/Publisher.h"

namespace Engine {

	class InputHandler {
	public:
		InputHandler(InputHandler& other) = delete;
		void operator=(const InputHandler&) = delete;

		static InputHandler* GetInstance();

		void Init(Window* window);

		Ref<Publisher<KeyboardEvent>> GetKeyPublisher() { return m_KeyboardInputPub; };

	protected:
		InputHandler() {};
		~InputHandler() = default;
	private:
		static InputHandler* s_InputHandler;
		static std::mutex s_Mutex;
		static bool m_Initialized;

		Ref<Publisher<KeyboardEvent>> m_KeyboardInputPub;
	};
}