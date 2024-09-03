#include <GLFW/glfw3.h>

#include "InputModule.hpp"

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

        if (!m_Initialized) {
            //glfwSetWindowUserPointer(GlfwWindow, this);

            //m_KeyboardInputPub = CreateRef<Publisher<KeyboardEvent>>();

            auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
                //InputModule* instance = (InputModule*)glfwGetWindowUserPointer(window);

                KeyAction k_action = (action == GLFW_PRESS) ? KeyAction::PRESSED : (action == GLFW_RELEASE) ? KeyAction::RELEASED : KeyAction::REPEAT;
                KeyModifiers k_mods = KeyModifiers();
                if (mods & GLFW_MOD_SHIFT) {
                    k_mods.MOD_SHIFT = true;
                }
                if (mods & GLFW_MOD_CONTROL) {
                    k_mods.MOD_CONTROL = true;
                }
                if (mods & GLFW_MOD_ALT) {
                    k_mods.MOD_ALT = true;
                }
                if (mods & GLFW_MOD_SUPER) {
                    k_mods.MOD_SUPER = true;
                }
                if (mods & GLFW_MOD_CAPS_LOCK) {
                    k_mods.MOD_CAPS_LOCK = true;
                }
                if (mods & GLFW_MOD_NUM_LOCK) {
                    k_mods.MOD_NUM_LOCK = true;
                }
                //TODO: Move platform specific input functionality to respective platform and map between platform keycodes and engine keycodes
                KeyEvent e = KeyEvent((KeyCode)key, k_action, k_mods);
                KeyboardEventsBus::Broadcast(&IKeyboardEvents::OnKeyEvent, e);
            };

            auto character_callback = [](GLFWwindow* window, uint32_t codepoint) {
                //InputModule* instance = (InputModule*)glfwGetWindowUserPointer(window);
                TextEvent e = TextEvent(codepoint);
                KeyboardEventsBus::Broadcast(&IKeyboardEvents::OnTextEvent, e);
            };

            auto cursor_enter_callback = [](GLFWwindow* window, int32_t entered) {
                //InputModule* instance = (InputModule*)glfwGetWindowUserPointer(window);
                //instance->m_Camera->mouse_callback(window, xposIn, yposIn);
                MouseCursorEnterEvent e = MouseCursorEnterEvent(entered);
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseCursorEnterEvent, e);
            };

            auto cursor_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
                //InputModule* instance = (InputModule*)glfwGetWindowUserPointer(window);
                //instance->m_Camera->mouse_callback(window, xposIn, yposIn);
                MouseCursorEvent e = MouseCursorEvent({xposIn, yposIn});
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseCursorEvent, e);
            };

            auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
                //InputModule* instance = (InputModule*)glfwGetWindowUserPointer(window);
                //instance->m_Camera->scroll_callback(window, xoffset, yoffset);
                MouseScrollEvent e = MouseScrollEvent({xoffset, yoffset});
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseScrollEvent, e);
            };

            auto mousebutton_callback = [](GLFWwindow* window, int button, int action, int mods) {
                KeyAction k_action = (action == GLFW_PRESS) ? KeyAction::PRESSED : (action == GLFW_RELEASE) ? KeyAction::RELEASED : KeyAction::REPEAT;
                KeyModifiers k_mods = KeyModifiers();
                if (mods & GLFW_MOD_SHIFT) {
                    k_mods.MOD_SHIFT = true;
                }
                if (mods & GLFW_MOD_CONTROL) {
                    k_mods.MOD_CONTROL = true;
                }
                if (mods & GLFW_MOD_ALT) {
                    k_mods.MOD_ALT = true;
                }
                if (mods & GLFW_MOD_SUPER) {
                    k_mods.MOD_SUPER = true;
                }
                if (mods & GLFW_MOD_CAPS_LOCK) {
                    k_mods.MOD_CAPS_LOCK = true;
                }
                if (mods & GLFW_MOD_NUM_LOCK) {
                    k_mods.MOD_NUM_LOCK = true;
                }
                MouseButtonEvent e = MouseButtonEvent((MouseButtonCode)button, k_action, k_mods);
                MouseEventsBus::Broadcast(&IMouseEvents::OnMouseButtonEvent, e);
            };

            glfwSetKeyCallback(GlfwWindow, key_callback);
            glfwSetCharCallback(GlfwWindow, character_callback);
            glfwSetCursorEnterCallback(GlfwWindow, cursor_enter_callback);
            glfwSetCursorPosCallback(GlfwWindow, cursor_callback);
            glfwSetScrollCallback(GlfwWindow, scroll_callback);
            glfwSetMouseButtonCallback(GlfwWindow, mousebutton_callback);

            m_Initialized = true;
        }
    }
}
