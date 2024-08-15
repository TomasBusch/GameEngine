#include "GLFW/glfw3.h"

#include "InputHandler.h"

Engine::InputHandler* Engine::InputHandler::s_InputHandler = nullptr;
std::mutex Engine::InputHandler::s_Mutex;
bool Engine::InputHandler::m_Initialized = false;

Engine::InputHandler* Engine::InputHandler::GetInstance() {
    
    std::lock_guard<std::mutex> lock(s_Mutex);
    if (s_InputHandler == nullptr) {
        s_InputHandler = new InputHandler();
    }

    return s_InputHandler;
}

void Engine::InputHandler::Init(Window* window)
{
    GLFWwindow* GlfwWindow = static_cast<GLFWwindow*>(window->getNativeHandle());

    if (!m_Initialized) {
        glfwSetWindowUserPointer(GlfwWindow, this);

        m_KeyboardInputPub = CreateRef<Publisher<KeyboardEvent>>();

        auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
            InputHandler* instance = (InputHandler*)glfwGetWindowUserPointer(window);
            //instance->updateViewportSize(width, height);
            //instance->m_Camera->setViewportSize(width, height);
            //glViewport(0, 0, width, height);
            };

        auto mouse_callback = [](GLFWwindow* window, double xposIn, double yposIn) {
            InputHandler* instance = (InputHandler*)glfwGetWindowUserPointer(window);
            //instance->m_Camera->mouse_callback(window, xposIn, yposIn);
            };

        auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
            InputHandler* instance = (InputHandler*)glfwGetWindowUserPointer(window);
            //instance->m_Camera->scroll_callback(window, xoffset, yoffset);
            };

        auto key_callback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            InputHandler* instance = (InputHandler*)glfwGetWindowUserPointer(window);
            //if (key == GLFW_KEY_LEFT_CONTROL && action == GLFW_RELEASE) {
            //    instance->m_Camera->toggleLock(window);
            //}
            if (key == GLFW_KEY_W) {
                KeyboardEvent e = KeyboardEvent("W");
                instance->GetInstance()->m_KeyboardInputPub->Publish(e);
            }
            };

        glfwSetFramebufferSizeCallback(GlfwWindow, framebuffer_size_callback);
        glfwSetCursorPosCallback(GlfwWindow, mouse_callback);
        glfwSetScrollCallback(GlfwWindow, scroll_callback);
        glfwSetKeyCallback(GlfwWindow, key_callback);

        m_Initialized = true;
    }
}
