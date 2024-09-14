#pragma once

#include "Platform/Input.hpp"

namespace Engine::Input {
	class GLFWInput : public PlatformInput {
    public:
        virtual void Init(void *window_handle) override;

        virtual void StartTextInput() override;
        virtual void StopTextInput() override;

        virtual void SetCursor(CursorState state) override;

        virtual void SetKeyCallback(KeyCallback cb) override;
        virtual void SetCharCallback(CharacterCallback cb) override;
        virtual void SetMouseEnterCallback(MouseEnterCallback cb) override;
        virtual void SetMousePosCallback(MousePositionCallback cb) override;
        virtual void SetScrollCallback(ScrollCallback cb) override;
        virtual void SetMouseButtonCallback(MouseButtonCallback cb) override;

    
	};
}