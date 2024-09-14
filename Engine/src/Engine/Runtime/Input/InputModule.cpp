#include <GLFW/glfw3.h>
#include <iostream>

#include "InputModule.hpp"
#include "Platform/GLFW/GLFWInput.hpp"
#include "Platform/SDL3/SDL3Input.hpp"

namespace Engine::Input {

    InputModule* InputModule::g_Instance = nullptr;
    std::mutex InputModule::s_Mutex;
    bool InputModule::m_Initialized = false;

    InputModule* InputModule::GetInstance() {

        std::lock_guard<std::mutex> lock(s_Mutex);
        if (g_Instance == nullptr) {
            g_Instance = new InputModule();
        }

        return g_Instance;
    }

    void InputModule::Init(Window* window)
    {
        GLFWwindow* GlfwWindow = static_cast<GLFWwindow*>(window->getNativeHandle());
        m_PlatformInput = CreateScope<SDL3Input>();

        if (!m_Initialized) {

            PlatformInput::KeyCallback key_callback = [](KeyCode kc, KeyAction ka, KeyModifiers km, scancode sc) {
                KeyEvent e = KeyEvent(kc, ka, km);
                KeyboardEventsBus::Broadcast(&IKeyboardEvents::OnKeyEvent, e);
            };

            PlatformInput::CharacterCallback character_callback = [](utf8_codepoint cp) {
                TextEvent e = TextEvent(cp);
                KeyboardEventsBus::Broadcast(&IKeyboardEvents::OnTextEvent, e);
            };

            PlatformInput::MouseEnterCallback mouse_enter_callback = [](bool entered) {
                if (entered) {
                    MouseEnterEvent e = MouseEnterEvent();
                    MouseEventsBus::Broadcast(&IMouseEvents::OnMouseEnterEvent, e);
                }
                else {
                    MouseLeaveEvent e = MouseLeaveEvent();
                    MouseEventsBus::Broadcast(&IMouseEvents::OnMouseLeaveEvent, e);
                }
            };

            PlatformInput::MousePositionCallback mouse_pos_callback = [](double xPos, double yPos, double xRel, double yRel) {
                MouseMoveEvent e = MouseMoveEvent({ xPos, yPos }, { xRel, yRel });
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseMoveEvent, e);
            };

            PlatformInput::ScrollCallback scroll_callback = [](double xoffset, double yoffset) {
                MouseScrollEvent e = MouseScrollEvent({xoffset, yoffset});
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseScrollEvent, e);
            };

            PlatformInput::MouseButtonCallback mouse_button_callback = [](MouseButtonCode mc, KeyAction ka) {
                MouseButtonEvent e = MouseButtonEvent(mc, ka);
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseButtonEvent, e);
            };

            m_PlatformInput->SetKeyCallback(key_callback);
            m_PlatformInput->SetCharCallback(character_callback);
            m_PlatformInput->SetMouseEnterCallback(mouse_enter_callback);
            m_PlatformInput->SetMousePosCallback(mouse_pos_callback);
            m_PlatformInput->SetScrollCallback(scroll_callback);
            m_PlatformInput->SetMouseButtonCallback(mouse_button_callback);

            m_PlatformInput->Init(window->getNativeHandle());

            m_Initialized = true;
        }
    }

    void InputModule::StartTextInput() 
    {
        m_PlatformInput->StartTextInput();
    }

    void InputModule::StopTextInput()
    {
        m_PlatformInput->StopTextInput();
    }

    void InputModule::SetCursor(PlatformInput::CursorState state) {
        m_PlatformInput->SetCursor(state);
    }
}
