#include "GLFWInput.hpp"

#include <GLFW/glfw3.h>


namespace Engine::Input {

    static KeyCode GLFWtoEngineKeyCode(int keycode);
    static MouseButtonCode GLFWtoEngineMousebuttonCode(uint8_t button);

    void GLFWInput::Init(void *window_handle)
    {
        m_WindowHandle = window_handle;
        GLFWwindow* GlfwWindow = (GLFWwindow*)window_handle;

        glfwSetWindowUserPointer(GlfwWindow, this);

        static auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            KeyAction k_action = (action == GLFW_PRESS) ? 
                KeyAction::PRESSED : (action == GLFW_RELEASE) ? 
                KeyAction::RELEASED : 
                KeyAction::REPEAT;
           
            KeyModifiers k_mods = KeyModifiers();
            k_mods.MOD_SHIFT = mods & GLFW_MOD_SHIFT;
                k_mods.MOD_CONTROL = mods & GLFW_MOD_CONTROL;
                k_mods.MOD_ALT = mods & GLFW_MOD_ALT;
                k_mods.MOD_SUPER = mods & GLFW_MOD_SUPER;
                k_mods.MOD_CAPS_LOCK = mods & GLFW_MOD_CAPS_LOCK;
                k_mods.MOD_NUM_LOCK = mods & GLFW_MOD_NUM_LOCK;

            if (instance->m_InputCallbacks.KeyCallback != nullptr) {
                instance->m_InputCallbacks.KeyCallback(GLFWtoEngineKeyCode(key), k_action, k_mods, scancode);
                return;
            }
        };

        static auto character_callback = [](GLFWwindow* window, uint32_t codepoint) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            if (instance->m_InputCallbacks.CharCallback != nullptr) {
                instance->m_InputCallbacks.CharCallback(codepoint);
            }
        };

        static auto cursor_enter_callback = [](GLFWwindow* window, int32_t entered) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            if (instance->m_InputCallbacks.MouseEnterCallback != nullptr) {
                instance->m_InputCallbacks.MouseEnterCallback((bool)entered);
            }
        };

        static auto cursor_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            if (instance->m_InputCallbacks.MousePosCallback != nullptr) {
                instance->m_InputCallbacks.MousePosCallback(xposIn, yposIn, xposIn, yposIn);
            }
        };

        static auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            if (instance->m_InputCallbacks.ScrollCallback != nullptr) {
                instance->m_InputCallbacks.ScrollCallback(xoffset, yoffset);
            }
        };

        static auto mousebutton_callback = [](GLFWwindow* window, int button, int action, int mods) {
            GLFWInput* instance = (GLFWInput*)glfwGetWindowUserPointer(window);

            KeyAction k_action = (action == GLFW_PRESS) ? KeyAction::PRESSED : (action == GLFW_RELEASE) ? KeyAction::RELEASED : KeyAction::REPEAT;

            if (instance->m_InputCallbacks.MouseButtonCallback != nullptr) {
                instance->m_InputCallbacks.MouseButtonCallback(GLFWtoEngineMousebuttonCode(button), k_action);
            }
        };

        glfwSetKeyCallback(GlfwWindow, key_callback);
        glfwSetCharCallback(GlfwWindow, character_callback);
        glfwSetCursorEnterCallback(GlfwWindow, cursor_enter_callback);
        glfwSetCursorPosCallback(GlfwWindow, cursor_callback);
        glfwSetScrollCallback(GlfwWindow, scroll_callback);
        glfwSetMouseButtonCallback(GlfwWindow, mousebutton_callback);
    }

    void GLFWInput::StartTextInput()
    {

    }

    void GLFWInput::StopTextInput()
    {

    }

    void GLFWInput::SetCursor(CursorState state)
    {

        if (state == CursorState::ENABLED) {
            glfwSetInputMode((GLFWwindow*)m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else if (state == CursorState::DISABLED) {
            glfwSetInputMode((GLFWwindow*)m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (state == CursorState::HIDDEN) {
            glfwSetInputMode((GLFWwindow*)m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        }
        else if (state == CursorState::CAPTURED) {
            glfwSetInputMode((GLFWwindow*)m_WindowHandle, GLFW_CURSOR, GLFW_CURSOR_CAPTURED);
        }
    }

    void GLFWInput::SetKeyCallback(KeyCallback cb)
    {
        m_InputCallbacks.KeyCallback = cb;
    }

    void GLFWInput::SetCharCallback(CharacterCallback cb)
    {
        m_InputCallbacks.CharCallback = cb;
    }

    void GLFWInput::SetMouseEnterCallback(MouseEnterCallback cb)
    {
        m_InputCallbacks.MouseEnterCallback = cb;
    }

    void GLFWInput::SetMousePosCallback(MousePositionCallback cb)
    {
        m_InputCallbacks.MousePosCallback = cb;
    }

    void GLFWInput::SetScrollCallback(ScrollCallback cb)
    {
        m_InputCallbacks.ScrollCallback = cb;
    }

    void GLFWInput::SetMouseButtonCallback(MouseButtonCallback cb)
    {
        m_InputCallbacks.MouseButtonCallback = cb;
    }

    static KeyCode GLFWtoEngineKeyCode(int keycode) {
        switch (keycode)
        {
        case GLFW_KEY_SPACE              : return KeyCode::SPACE;break;
        case GLFW_KEY_APOSTROPHE         : return KeyCode::APOSTROPHE;break;
        case GLFW_KEY_COMMA              : return KeyCode::COMMA;break;
        case GLFW_KEY_MINUS              : return KeyCode::MINUS;break;
        case GLFW_KEY_PERIOD             : return KeyCode::PERIOD;break;
        case GLFW_KEY_SLASH              : return KeyCode::SLASH;break;
        case GLFW_KEY_0                  : return KeyCode::NUM_0;break;
        case GLFW_KEY_1                  : return KeyCode::NUM_1;break;
        case GLFW_KEY_2                  : return KeyCode::NUM_2;break;
        case GLFW_KEY_3                  : return KeyCode::NUM_3;break;
        case GLFW_KEY_4                  : return KeyCode::NUM_4;break;
        case GLFW_KEY_5                  : return KeyCode::NUM_5;break;
        case GLFW_KEY_6                  : return KeyCode::NUM_6;break;
        case GLFW_KEY_7                  : return KeyCode::NUM_7;break;
        case GLFW_KEY_8                  : return KeyCode::NUM_8;break;
        case GLFW_KEY_9                  : return KeyCode::NUM_9;break;
        case GLFW_KEY_SEMICOLON          : return KeyCode::SEMICOLON;break;
        case GLFW_KEY_EQUAL              : return KeyCode::EQUALS;break;
        case GLFW_KEY_A                  : return KeyCode::A;break;
        case GLFW_KEY_B                  : return KeyCode::B;break;
        case GLFW_KEY_C                  : return KeyCode::C;break;
        case GLFW_KEY_D                  : return KeyCode::D;break;
        case GLFW_KEY_E                  : return KeyCode::E;break;
        case GLFW_KEY_F                  : return KeyCode::F;break;
        case GLFW_KEY_G                  : return KeyCode::G;break;
        case GLFW_KEY_H                  : return KeyCode::H;break;
        case GLFW_KEY_I                  : return KeyCode::I;break;
        case GLFW_KEY_J                  : return KeyCode::J;break;
        case GLFW_KEY_K                  : return KeyCode::K;break;
        case GLFW_KEY_L                  : return KeyCode::L;break;
        case GLFW_KEY_M                  : return KeyCode::M;break;
        case GLFW_KEY_N                  : return KeyCode::N;break;
        case GLFW_KEY_O                  : return KeyCode::O;break;
        case GLFW_KEY_P                  : return KeyCode::P;break;
        case GLFW_KEY_Q                  : return KeyCode::Q;break;
        case GLFW_KEY_R                  : return KeyCode::R;break;
        case GLFW_KEY_S                  : return KeyCode::S;break;
        case GLFW_KEY_T                  : return KeyCode::T;break;
        case GLFW_KEY_U                  : return KeyCode::U;break;
        case GLFW_KEY_V                  : return KeyCode::V;break;
        case GLFW_KEY_W                  : return KeyCode::W;break;
        case GLFW_KEY_X                  : return KeyCode::X;break;
        case GLFW_KEY_Y                  : return KeyCode::Y;break;
        case GLFW_KEY_Z                  : return KeyCode::Z;break;
        case GLFW_KEY_LEFT_BRACKET       : return KeyCode::LEFTBRACKET;break;
        case GLFW_KEY_BACKSLASH          : return KeyCode::BACKSLASH;break;
        case GLFW_KEY_RIGHT_BRACKET      : return KeyCode::RIGHTBRACKET;break;
        case GLFW_KEY_GRAVE_ACCENT       : return KeyCode::GRAVE;break;
        case GLFW_KEY_WORLD_1            : return KeyCode::UNKNOWN;break; //TODO: Check
        case GLFW_KEY_WORLD_2            : return KeyCode::UNKNOWN;break; //TODO: Check
        case GLFW_KEY_ESCAPE             : return KeyCode::ESCAPE;break;
        case GLFW_KEY_ENTER              : return KeyCode::KP_ENTER;break;
        case GLFW_KEY_TAB                : return KeyCode::TAB;break;
        case GLFW_KEY_BACKSPACE          : return KeyCode::BACKSPACE;break;
        case GLFW_KEY_INSERT             : return KeyCode::INSERT;break;
        case GLFW_KEY_DELETE             : return KeyCode::DELETE;break;
        case GLFW_KEY_RIGHT              : return KeyCode::RIGHT;break;
        case GLFW_KEY_LEFT               : return KeyCode::LEFT;break;
        case GLFW_KEY_DOWN               : return KeyCode::DOWN;break;
        case GLFW_KEY_UP                 : return KeyCode::UP;break;
        case GLFW_KEY_PAGE_UP            : return KeyCode::PAGEUP;break;
        case GLFW_KEY_PAGE_DOWN          : return KeyCode::PAGEDOWN;break;
        case GLFW_KEY_HOME               : return KeyCode::HOME;break;
        case GLFW_KEY_END                : return KeyCode::END;break;
        case GLFW_KEY_CAPS_LOCK          : return KeyCode::CAPSLOCK;break;
        case GLFW_KEY_SCROLL_LOCK        : return KeyCode::SCROLLLOCK;break;
        case GLFW_KEY_NUM_LOCK           : return KeyCode::NUMLOCKCLEAR;break;
        case GLFW_KEY_PRINT_SCREEN       : return KeyCode::PRINTSCREEN;break;
        case GLFW_KEY_PAUSE              : return KeyCode::PAUSE;break; //TODO: Check
        case GLFW_KEY_F1                 : return KeyCode::F1;break;
        case GLFW_KEY_F2                 : return KeyCode::F2;break;
        case GLFW_KEY_F3                 : return KeyCode::F3;break;
        case GLFW_KEY_F4                 : return KeyCode::F4;break;
        case GLFW_KEY_F5                 : return KeyCode::F5;break;
        case GLFW_KEY_F6                 : return KeyCode::F6;break;
        case GLFW_KEY_F7                 : return KeyCode::F7;break;
        case GLFW_KEY_F8                 : return KeyCode::F8;break;
        case GLFW_KEY_F9                 : return KeyCode::F9;break;
        case GLFW_KEY_F10                : return KeyCode::F10;break;
        case GLFW_KEY_F11                : return KeyCode::F11;break;
        case GLFW_KEY_F12                : return KeyCode::F12;break;
        case GLFW_KEY_F13                : return KeyCode::F13;break;
        case GLFW_KEY_F14                : return KeyCode::F14;break;
        case GLFW_KEY_F15                : return KeyCode::F15;break;
        case GLFW_KEY_F16                : return KeyCode::F16;break;
        case GLFW_KEY_F17                : return KeyCode::F17;break;
        case GLFW_KEY_F18                : return KeyCode::F18;break;
        case GLFW_KEY_F19                : return KeyCode::F19;break;
        case GLFW_KEY_F20                : return KeyCode::F20;break;
        case GLFW_KEY_F21                : return KeyCode::F21;break;
        case GLFW_KEY_F22                : return KeyCode::F22;break;
        case GLFW_KEY_F23                : return KeyCode::F23;break;
        case GLFW_KEY_F24                : return KeyCode::F24;break;
        case GLFW_KEY_F25                : return KeyCode::UNKNOWN;break; //TODO: Check
        case GLFW_KEY_KP_0               : return KeyCode::KP_0;break;
        case GLFW_KEY_KP_1               : return KeyCode::KP_1;break;
        case GLFW_KEY_KP_2               : return KeyCode::KP_2;break;
        case GLFW_KEY_KP_3               : return KeyCode::KP_3;break;
        case GLFW_KEY_KP_4               : return KeyCode::KP_4;break;
        case GLFW_KEY_KP_5               : return KeyCode::KP_5;break;
        case GLFW_KEY_KP_6               : return KeyCode::KP_6;break;
        case GLFW_KEY_KP_7               : return KeyCode::KP_7;break;
        case GLFW_KEY_KP_8               : return KeyCode::KP_8;break;
        case GLFW_KEY_KP_9               : return KeyCode::KP_9;break;
        case GLFW_KEY_KP_DECIMAL         : return KeyCode::KP_DECIMAL;break;
        case GLFW_KEY_KP_DIVIDE          : return KeyCode::KP_DIVIDE;break;
        case GLFW_KEY_KP_MULTIPLY        : return KeyCode::KP_MULTIPLY;break;
        case GLFW_KEY_KP_SUBTRACT        : return KeyCode::KP_MEMSUBTRACT;break;
        case GLFW_KEY_KP_ADD             : return KeyCode::KP_MEMADD;break;
        case GLFW_KEY_KP_ENTER           : return KeyCode::KP_ENTER;break;
        case GLFW_KEY_KP_EQUAL           : return KeyCode::KP_EQUALS;break;
        case GLFW_KEY_LEFT_SHIFT         : return KeyCode::LSHIFT;break;
        case GLFW_KEY_LEFT_CONTROL       : return KeyCode::LCTRL;break;
        case GLFW_KEY_LEFT_ALT           : return KeyCode::LALT;break;
        case GLFW_KEY_LEFT_SUPER         : return KeyCode::HOME;break; //TODO: Check
        case GLFW_KEY_RIGHT_SHIFT        : return KeyCode::RSHIFT;break;
        case GLFW_KEY_RIGHT_CONTROL      : return KeyCode::RCTRL;break;
        case GLFW_KEY_RIGHT_ALT          : return KeyCode::RALT;break;
        case GLFW_KEY_RIGHT_SUPER        : return KeyCode::HOME;break; //TODO: Check
        case GLFW_KEY_MENU               : return KeyCode::MENU;break;
        default:return KeyCode::UNKNOWN;
        }
    }

    static MouseButtonCode GLFWtoEngineMousebuttonCode(uint8_t button) {
        return (MouseButtonCode)(button - 1);
    }
}