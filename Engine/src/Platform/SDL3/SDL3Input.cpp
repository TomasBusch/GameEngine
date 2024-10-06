#include "SDL3Input.hpp"
#include "Engine/Core/Utils/Strings/utf.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

namespace Engine::Input {

    static KeyCode SDL3toEngineKeyCode(SDL_Keycode keycode);
    static MouseButtonCode SDL3toEngineMousebuttonCode(uint8_t button);

    void SDL3Input::Init(void *window_handle)
    {
        m_WindowHandle = window_handle;
        SDL_Window* window = (SDL_Window*)window_handle;

        static SDL_EventFilter keyboardFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_KEY_DOWN:
            case SDL_EventType::SDL_EVENT_KEY_UP:
            {

                KeyCode k_keycode = SDL3toEngineKeyCode(event->key.key);

                KeyAction k_action = (event->key.repeat) ?
                    KeyAction::REPEAT :
                    (event->type == SDL_EventType::SDL_EVENT_KEY_DOWN) ?
                    KeyAction::PRESSED :
                    KeyAction::RELEASED;

                KeyModifiers k_mods;
                k_mods.MOD_SHIFT = (event->key.mod & SDL_KMOD_SHIFT);
                k_mods.MOD_CONTROL = (event->key.mod & SDL_KMOD_CTRL);
                k_mods.MOD_ALT = (event->key.mod & SDL_KMOD_ALT);
                k_mods.MOD_SUPER = (event->key.mod & SDL_KMOD_GUI);
                k_mods.MOD_CAPS_LOCK = (event->key.mod & SDL_KMOD_CAPS);
                k_mods.MOD_NUM_LOCK = (event->key.mod & SDL_KMOD_NUM);

                if (instance->m_InputCallbacks.KeyCallback != nullptr) {
                    instance->m_InputCallbacks.KeyCallback(k_keycode, k_action, k_mods, event->key.scancode);
                    return 1;
                }
                return 0;
            }
            break;
            default: return 0;
            }
        };

        static SDL_EventFilter charFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_TEXT_INPUT:
            {
                char32_t codepoint;
                codepoint = ::Engine::Utils::UTF8toChar32_t(event->text.text);

                if (instance->m_InputCallbacks.CharCallback != nullptr) {
                    instance->m_InputCallbacks.CharCallback(codepoint);
                    return 1;
                }
                return 0;
            }
            break;

            default: return 0;
            }
        };

        static SDL_EventFilter mouseEnterFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_WINDOW_MOUSE_ENTER:
            case SDL_EventType::SDL_EVENT_WINDOW_MOUSE_LEAVE:
            {
                if (instance->m_InputCallbacks.MouseEnterCallback != nullptr) {
                    instance->m_InputCallbacks.MouseEnterCallback(event->type == SDL_EventType::SDL_EVENT_WINDOW_MOUSE_ENTER);
                    return 1;
                }
                return 0;
            }
            break;

            default: return 0;
            }
        };

        static SDL_EventFilter mousePosFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_MOUSE_MOTION:
            {
                if (instance->m_InputCallbacks.MousePosCallback != nullptr) {
                    instance->m_InputCallbacks.MousePosCallback(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel);
                    return 1;
                }
                return 0;
            }
            break;

            default: return 0;
            }
        };

        static SDL_EventFilter scrollFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_MOUSE_WHEEL:
            {

                if (instance->m_InputCallbacks.ScrollCallback != nullptr) {
                    instance->m_InputCallbacks.ScrollCallback(event->wheel.x, event->wheel.y);
                    return 1;
                }
                return 0;
            }
            break;

            default: return 0;
            }
        };

        static SDL_EventFilter mouseButtonFilter = [](void* thisptr, SDL_Event* event) -> bool {
            SDL3Input* instance = (SDL3Input*)thisptr;
            switch (event->type)
            {
            case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN:
            case SDL_EventType::SDL_EVENT_MOUSE_BUTTON_UP:
            {

                MouseButtonCode k_buttoncode = SDL3toEngineMousebuttonCode(event->button.button);

                SDL_BUTTON_LEFT;
                SDL_BUTTON_MIDDLE;
                SDL_BUTTON_RIGHT;
                SDL_BUTTON_X1;
                SDL_BUTTON_X2;

                KeyAction k_action = (event->type == SDL_EventType::SDL_EVENT_MOUSE_BUTTON_DOWN) ?
                    KeyAction::PRESSED :
                    KeyAction::RELEASED;

                KeyModifiers k_mods;
                k_mods.MOD_SHIFT = (event->key.mod & SDL_KMOD_SHIFT);
                k_mods.MOD_CONTROL = (event->key.mod & SDL_KMOD_CTRL);
                k_mods.MOD_ALT = (event->key.mod & SDL_KMOD_ALT);
                k_mods.MOD_SUPER = (event->key.mod & SDL_KMOD_GUI);
                k_mods.MOD_CAPS_LOCK = (event->key.mod & SDL_KMOD_CAPS);
                k_mods.MOD_NUM_LOCK = (event->key.mod & SDL_KMOD_NUM);


                if (instance->m_InputCallbacks.ScrollCallback != nullptr) {
                    instance->m_InputCallbacks.MouseButtonCallback(k_buttoncode, k_action);
                    return 1;
                }
                return 0;
            }
            break;

            default: return 0;
            }
        };

        SDL_AddEventWatch(keyboardFilter, this);
        SDL_AddEventWatch(charFilter, this);
        SDL_AddEventWatch(mouseEnterFilter, this);
        SDL_AddEventWatch(mousePosFilter, this);
        SDL_AddEventWatch(scrollFilter, this);
        SDL_AddEventWatch(mouseButtonFilter, this);
    }

    void SDL3Input::StartTextInput()
    {
        SDL_StartTextInput((SDL_Window*)m_WindowHandle);
    }

    void SDL3Input::StopTextInput()
    {
        SDL_StopTextInput((SDL_Window*)m_WindowHandle);
    }

    void SDL3Input::SetCursor(CursorState state)
    {

        if (state == CursorState::ENABLED) {
            SDL_ShowCursor();
            SDL_CaptureMouse(false);
            //SDL_SetRelativeMouseMode(false);
        }
        else if (state == CursorState::DISABLED) {
            SDL_HideCursor();
            SDL_CaptureMouse(true);
            //This seems to be close to being depracated in favor of SDL_SetWindowRelativeMouseMode(), however it does not seem to be implemented yet
            //SDL_SetRelativeMouseMode(true);
        }
        else if (state == CursorState::HIDDEN) {
            SDL_HideCursor();
            SDL_CaptureMouse(false);
            //SDL_SetRelativeMouseMode(false);
        }
        else if (state == CursorState::CAPTURED) {
            SDL_ShowCursor();
            SDL_CaptureMouse(true);
            //SDL_SetRelativeMouseMode(false);
        }
    }

    void SDL3Input::SetKeyCallback(KeyCallback cb)
    {

        m_InputCallbacks.KeyCallback = cb;
    };
    
    void SDL3Input::SetCharCallback(CharacterCallback cb)
    {
        m_InputCallbacks.CharCallback = cb;
    };

    void SDL3Input::SetMouseEnterCallback(MouseEnterCallback cb)
    {
        m_InputCallbacks.MouseEnterCallback = cb;
    };

    void SDL3Input::SetMousePosCallback(MousePositionCallback cb)
    {
        m_InputCallbacks.MousePosCallback = cb;
    };

    void SDL3Input::SetScrollCallback(ScrollCallback cb)
    {
        m_InputCallbacks.ScrollCallback = cb;
    };

    void SDL3Input::SetMouseButtonCallback(MouseButtonCallback cb)
    {
        m_InputCallbacks.MouseButtonCallback = cb;
    };

    static KeyCode SDL3toEngineKeyCode(SDL_Keycode keycode) {
        switch (keycode) 
        {
            case SDLK_UNKNOWN                :return KeyCode::UNKNOWN                ;break;
            case SDLK_RETURN                 :return KeyCode::RETURN                 ;break;
            case SDLK_ESCAPE                 :return KeyCode::ESCAPE                 ;break;
            case SDLK_BACKSPACE              :return KeyCode::BACKSPACE              ;break;
            case SDLK_TAB                    :return KeyCode::TAB                    ;break;
            case SDLK_SPACE                  :return KeyCode::SPACE                  ;break;
            case SDLK_EXCLAIM                :return KeyCode::EXCLAIM                ;break;
            case SDLK_DBLAPOSTROPHE          :return KeyCode::DBLAPOSTROPHE          ;break;
            case SDLK_HASH                   :return KeyCode::HASH                   ;break;
            case SDLK_DOLLAR                 :return KeyCode::DOLLAR                 ;break;
            case SDLK_PERCENT                :return KeyCode::PERCENT                ;break;
            case SDLK_AMPERSAND              :return KeyCode::AMPERSAND              ;break;
            case SDLK_APOSTROPHE             :return KeyCode::APOSTROPHE             ;break;
            case SDLK_LEFTPAREN              :return KeyCode::LEFTPAREN              ;break;
            case SDLK_RIGHTPAREN             :return KeyCode::RIGHTPAREN             ;break;
            case SDLK_ASTERISK               :return KeyCode::ASTERISK               ;break;
            case SDLK_PLUS                   :return KeyCode::PLUS                   ;break;
            case SDLK_COMMA                  :return KeyCode::COMMA                  ;break;
            case SDLK_MINUS                  :return KeyCode::MINUS                  ;break;
            case SDLK_PERIOD                 :return KeyCode::PERIOD                 ;break;
            case SDLK_SLASH                  :return KeyCode::SLASH                  ;break;
            case SDLK_0                      :return KeyCode::NUM_0                  ;break;
            case SDLK_1                      :return KeyCode::NUM_1                  ;break;
            case SDLK_2                      :return KeyCode::NUM_2                  ;break;
            case SDLK_3                      :return KeyCode::NUM_3                  ;break;
            case SDLK_4                      :return KeyCode::NUM_4                  ;break;
            case SDLK_5                      :return KeyCode::NUM_5                  ;break;
            case SDLK_6                      :return KeyCode::NUM_6                  ;break;
            case SDLK_7                      :return KeyCode::NUM_7                  ;break;
            case SDLK_8                      :return KeyCode::NUM_8                  ;break;
            case SDLK_9                      :return KeyCode::NUM_9                  ;break;
            case SDLK_COLON                  :return KeyCode::COLON                  ;break;
            case SDLK_SEMICOLON              :return KeyCode::SEMICOLON              ;break;
            case SDLK_LESS                   :return KeyCode::LESS                   ;break;
            case SDLK_EQUALS                 :return KeyCode::EQUALS                 ;break;
            case SDLK_GREATER                :return KeyCode::GREATER                ;break;
            case SDLK_QUESTION               :return KeyCode::QUESTION               ;break;
            case SDLK_AT                     :return KeyCode::AT                     ;break;
            case SDLK_LEFTBRACKET            :return KeyCode::LEFTBRACKET            ;break;
            case SDLK_BACKSLASH              :return KeyCode::BACKSLASH              ;break;
            case SDLK_RIGHTBRACKET           :return KeyCode::RIGHTBRACKET           ;break;
            case SDLK_CARET                  :return KeyCode::CARET                  ;break;
            case SDLK_UNDERSCORE             :return KeyCode::UNDERSCORE             ;break;
            case SDLK_GRAVE                  :return KeyCode::GRAVE                  ;break;
            case SDLK_A                      :return KeyCode::A                      ;break;
            case SDLK_B                      :return KeyCode::B                      ;break;
            case SDLK_C                      :return KeyCode::C                      ;break;
            case SDLK_D                      :return KeyCode::D                      ;break;
            case SDLK_E                      :return KeyCode::E                      ;break;
            case SDLK_F                      :return KeyCode::F                      ;break;
            case SDLK_G                      :return KeyCode::G                      ;break;
            case SDLK_H                      :return KeyCode::H                      ;break;
            case SDLK_I                      :return KeyCode::I                      ;break;
            case SDLK_J                      :return KeyCode::J                      ;break;
            case SDLK_K                      :return KeyCode::K                      ;break;
            case SDLK_L                      :return KeyCode::L                      ;break;
            case SDLK_M                      :return KeyCode::M                      ;break;
            case SDLK_N                      :return KeyCode::N                      ;break;
            case SDLK_O                      :return KeyCode::O                      ;break;
            case SDLK_P                      :return KeyCode::P                      ;break;
            case SDLK_Q                      :return KeyCode::Q                      ;break;
            case SDLK_R                      :return KeyCode::R                      ;break;
            case SDLK_S                      :return KeyCode::S                      ;break;
            case SDLK_T                      :return KeyCode::T                      ;break;
            case SDLK_U                      :return KeyCode::U                      ;break;
            case SDLK_V                      :return KeyCode::V                      ;break;
            case SDLK_W                      :return KeyCode::W                      ;break;
            case SDLK_X                      :return KeyCode::X                      ;break;
            case SDLK_Y                      :return KeyCode::Y                      ;break;
            case SDLK_Z                      :return KeyCode::Z                      ;break;
            case SDLK_LEFTBRACE              :return KeyCode::LEFTBRACE              ;break;
            case SDLK_PIPE                   :return KeyCode::PIPE                   ;break;
            case SDLK_RIGHTBRACE             :return KeyCode::RIGHTBRACE             ;break;
            case SDLK_TILDE                  :return KeyCode::TILDE                  ;break;
            case SDLK_DELETE                 :return KeyCode::DELETE                 ;break;
            case SDLK_PLUSMINUS              :return KeyCode::PLUSMINUS              ;break;
            case SDLK_CAPSLOCK               :return KeyCode::CAPSLOCK               ;break;
            case SDLK_F1                     :return KeyCode::F1                     ;break;
            case SDLK_F2                     :return KeyCode::F2                     ;break;
            case SDLK_F3                     :return KeyCode::F3                     ;break;
            case SDLK_F4                     :return KeyCode::F4                     ;break;
            case SDLK_F5                     :return KeyCode::F5                     ;break;
            case SDLK_F6                     :return KeyCode::F6                     ;break;
            case SDLK_F7                     :return KeyCode::F7                     ;break;
            case SDLK_F8                     :return KeyCode::F8                     ;break;
            case SDLK_F9                     :return KeyCode::F9                     ;break;
            case SDLK_F10                    :return KeyCode::F10                    ;break;
            case SDLK_F11                    :return KeyCode::F11                    ;break;
            case SDLK_F12                    :return KeyCode::F12                    ;break;
            case SDLK_PRINTSCREEN            :return KeyCode::PRINTSCREEN            ;break;
            case SDLK_SCROLLLOCK             :return KeyCode::SCROLLLOCK             ;break;
            case SDLK_PAUSE                  :return KeyCode::PAUSE                  ;break;
            case SDLK_INSERT                 :return KeyCode::INSERT                 ;break;
            case SDLK_HOME                   :return KeyCode::HOME                   ;break;
            case SDLK_PAGEUP                 :return KeyCode::PAGEUP                 ;break;
            case SDLK_END                    :return KeyCode::END                    ;break;
            case SDLK_PAGEDOWN               :return KeyCode::PAGEDOWN               ;break;
            case SDLK_RIGHT                  :return KeyCode::RIGHT                  ;break;
            case SDLK_LEFT                   :return KeyCode::LEFT                   ;break;
            case SDLK_DOWN                   :return KeyCode::DOWN                   ;break;
            case SDLK_UP                     :return KeyCode::UP                     ;break;
            case SDLK_NUMLOCKCLEAR           :return KeyCode::NUMLOCKCLEAR           ;break;
            case SDLK_KP_DIVIDE              :return KeyCode::KP_DIVIDE              ;break;
            case SDLK_KP_MULTIPLY            :return KeyCode::KP_MULTIPLY            ;break;
            case SDLK_KP_MINUS               :return KeyCode::KP_MINUS               ;break;
            case SDLK_KP_PLUS                :return KeyCode::KP_PLUS                ;break;
            case SDLK_KP_ENTER               :return KeyCode::KP_ENTER               ;break;
            case SDLK_KP_1                   :return KeyCode::KP_1                   ;break;
            case SDLK_KP_2                   :return KeyCode::KP_2                   ;break;
            case SDLK_KP_3                   :return KeyCode::KP_3                   ;break;
            case SDLK_KP_4                   :return KeyCode::KP_4                   ;break;
            case SDLK_KP_5                   :return KeyCode::KP_5                   ;break;
            case SDLK_KP_6                   :return KeyCode::KP_6                   ;break;
            case SDLK_KP_7                   :return KeyCode::KP_7                   ;break;
            case SDLK_KP_8                   :return KeyCode::KP_8                   ;break;
            case SDLK_KP_9                   :return KeyCode::KP_9                   ;break;
            case SDLK_KP_0                   :return KeyCode::KP_0                   ;break;
            case SDLK_KP_PERIOD              :return KeyCode::KP_PERIOD              ;break;
            case SDLK_APPLICATION            :return KeyCode::APPLICATION            ;break;
            case SDLK_POWER                  :return KeyCode::POWER                  ;break;
            case SDLK_KP_EQUALS              :return KeyCode::KP_EQUALS              ;break;
            case SDLK_F13                    :return KeyCode::F13                    ;break;
            case SDLK_F14                    :return KeyCode::F14                    ;break;
            case SDLK_F15                    :return KeyCode::F15                    ;break;
            case SDLK_F16                    :return KeyCode::F16                    ;break;
            case SDLK_F17                    :return KeyCode::F17                    ;break;
            case SDLK_F18                    :return KeyCode::F18                    ;break;
            case SDLK_F19                    :return KeyCode::F19                    ;break;
            case SDLK_F20                    :return KeyCode::F20                    ;break;
            case SDLK_F21                    :return KeyCode::F21                    ;break;
            case SDLK_F22                    :return KeyCode::F22                    ;break;
            case SDLK_F23                    :return KeyCode::F23                    ;break;
            case SDLK_F24                    :return KeyCode::F24                    ;break;
            case SDLK_EXECUTE                :return KeyCode::EXECUTE                ;break;
            case SDLK_HELP                   :return KeyCode::HELP                   ;break;
            case SDLK_MENU                   :return KeyCode::MENU                   ;break;
            case SDLK_SELECT                 :return KeyCode::SELECT                 ;break;
            case SDLK_STOP                   :return KeyCode::STOP                   ;break;
            case SDLK_AGAIN                  :return KeyCode::AGAIN                  ;break;
            case SDLK_UNDO                   :return KeyCode::UNDO                   ;break;
            case SDLK_CUT                    :return KeyCode::CUT                    ;break;
            case SDLK_COPY                   :return KeyCode::COPY                   ;break;
            case SDLK_PASTE                  :return KeyCode::PASTE                  ;break;
            case SDLK_FIND                   :return KeyCode::FIND                   ;break;
            case SDLK_MUTE                   :return KeyCode::MUTE                   ;break;
            case SDLK_VOLUMEUP               :return KeyCode::VOLUMEUP               ;break;
            case SDLK_VOLUMEDOWN             :return KeyCode::VOLUMEDOWN             ;break;
            case SDLK_KP_COMMA               :return KeyCode::KP_COMMA               ;break;
            case SDLK_KP_EQUALSAS400         :return KeyCode::KP_EQUALSAS400         ;break;
            case SDLK_ALTERASE               :return KeyCode::ALTERASE               ;break;
            case SDLK_SYSREQ                 :return KeyCode::SYSREQ                 ;break;
            case SDLK_CANCEL                 :return KeyCode::CANCEL                 ;break;
            case SDLK_CLEAR                  :return KeyCode::CLEAR                  ;break;
            case SDLK_PRIOR                  :return KeyCode::PRIOR                  ;break;
            case SDLK_RETURN2                :return KeyCode::RETURN2                ;break;
            case SDLK_SEPARATOR              :return KeyCode::SEPARATOR              ;break;
            case SDLK_OUT                    :return KeyCode::OUT                    ;break;
            case SDLK_OPER                   :return KeyCode::OPER                   ;break;
            case SDLK_CLEARAGAIN             :return KeyCode::CLEARAGAIN             ;break;
            case SDLK_CRSEL                  :return KeyCode::CRSEL                  ;break;
            case SDLK_EXSEL                  :return KeyCode::EXSEL                  ;break;
            case SDLK_KP_00                  :return KeyCode::KP_00                  ;break;
            case SDLK_KP_000                 :return KeyCode::KP_000                 ;break;
            case SDLK_THOUSANDSSEPARATOR     :return KeyCode::THOUSANDSSEPARATOR     ;break;
            case SDLK_DECIMALSEPARATOR       :return KeyCode::DECIMALSEPARATOR       ;break;
            case SDLK_CURRENCYUNIT           :return KeyCode::CURRENCYUNIT           ;break;
            case SDLK_CURRENCYSUBUNIT        :return KeyCode::CURRENCYSUBUNIT        ;break;
            case SDLK_KP_LEFTPAREN           :return KeyCode::KP_LEFTPAREN           ;break;
            case SDLK_KP_RIGHTPAREN          :return KeyCode::KP_RIGHTPAREN          ;break;
            case SDLK_KP_LEFTBRACE           :return KeyCode::KP_LEFTBRACE           ;break;
            case SDLK_KP_RIGHTBRACE          :return KeyCode::KP_RIGHTBRACE          ;break;
            case SDLK_KP_TAB                 :return KeyCode::KP_TAB                 ;break;
            case SDLK_KP_BACKSPACE           :return KeyCode::KP_BACKSPACE           ;break;
            case SDLK_KP_A                   :return KeyCode::KP_A                   ;break;
            case SDLK_KP_B                   :return KeyCode::KP_B                   ;break;
            case SDLK_KP_C                   :return KeyCode::KP_C                   ;break;
            case SDLK_KP_D                   :return KeyCode::KP_D                   ;break;
            case SDLK_KP_E                   :return KeyCode::KP_E                   ;break;
            case SDLK_KP_F                   :return KeyCode::KP_F                   ;break;
            case SDLK_KP_XOR                 :return KeyCode::KP_XOR                 ;break;
            case SDLK_KP_POWER               :return KeyCode::KP_POWER               ;break;
            case SDLK_KP_PERCENT             :return KeyCode::KP_PERCENT             ;break;
            case SDLK_KP_LESS                :return KeyCode::KP_LESS                ;break;
            case SDLK_KP_GREATER             :return KeyCode::KP_GREATER             ;break;
            case SDLK_KP_AMPERSAND           :return KeyCode::KP_AMPERSAND           ;break;
            case SDLK_KP_DBLAMPERSAND        :return KeyCode::KP_DBLAMPERSAND        ;break;
            case SDLK_KP_VERTICALBAR         :return KeyCode::KP_VERTICALBAR         ;break;
            case SDLK_KP_DBLVERTICALBAR      :return KeyCode::KP_DBLVERTICALBAR      ;break;
            case SDLK_KP_COLON               :return KeyCode::KP_COLON               ;break;
            case SDLK_KP_HASH                :return KeyCode::KP_HASH                ;break;
            case SDLK_KP_SPACE               :return KeyCode::KP_SPACE               ;break;
            case SDLK_KP_AT                  :return KeyCode::KP_AT                  ;break;
            case SDLK_KP_EXCLAM              :return KeyCode::KP_EXCLAM              ;break;
            case SDLK_KP_MEMSTORE            :return KeyCode::KP_MEMSTORE            ;break;
            case SDLK_KP_MEMRECALL           :return KeyCode::KP_MEMRECALL           ;break;
            case SDLK_KP_MEMCLEAR            :return KeyCode::KP_MEMCLEAR            ;break;
            case SDLK_KP_MEMADD              :return KeyCode::KP_MEMADD              ;break;
            case SDLK_KP_MEMSUBTRACT         :return KeyCode::KP_MEMSUBTRACT         ;break;
            case SDLK_KP_MEMMULTIPLY         :return KeyCode::KP_MEMMULTIPLY         ;break;
            case SDLK_KP_MEMDIVIDE           :return KeyCode::KP_MEMDIVIDE           ;break;
            case SDLK_KP_PLUSMINUS           :return KeyCode::KP_PLUSMINUS           ;break;
            case SDLK_KP_CLEAR               :return KeyCode::KP_CLEAR               ;break;
            case SDLK_KP_CLEARENTRY          :return KeyCode::KP_CLEARENTRY          ;break;
            case SDLK_KP_BINARY              :return KeyCode::KP_BINARY              ;break;
            case SDLK_KP_OCTAL               :return KeyCode::KP_OCTAL               ;break;
            case SDLK_KP_DECIMAL             :return KeyCode::KP_DECIMAL             ;break;
            case SDLK_KP_HEXADECIMAL         :return KeyCode::KP_HEXADECIMAL         ;break;
            case SDLK_LCTRL                  :return KeyCode::LCTRL                  ;break;
            case SDLK_LSHIFT                 :return KeyCode::LSHIFT                 ;break;
            case SDLK_LALT                   :return KeyCode::LALT                   ;break;
            case SDLK_LGUI                   :return KeyCode::LGUI                   ;break;
            case SDLK_RCTRL                  :return KeyCode::RCTRL                  ;break;
            case SDLK_RSHIFT                 :return KeyCode::RSHIFT                 ;break;
            case SDLK_RALT                   :return KeyCode::RALT                   ;break;
            case SDLK_RGUI                   :return KeyCode::RGUI                   ;break;
            case SDLK_MODE                   :return KeyCode::MODE                   ;break;
            case SDLK_SLEEP                  :return KeyCode::SLEEP                  ;break;
            case SDLK_WAKE                   :return KeyCode::WAKE                   ;break;
            case SDLK_CHANNEL_INCREMENT      :return KeyCode::CHANNEL_INCREMENT      ;break;
            case SDLK_CHANNEL_DECREMENT      :return KeyCode::CHANNEL_DECREMENT      ;break;
            case SDLK_MEDIA_PLAY             :return KeyCode::MEDIA_PLAY             ;break;
            case SDLK_MEDIA_PAUSE            :return KeyCode::MEDIA_PAUSE            ;break;
            case SDLK_MEDIA_RECORD           :return KeyCode::MEDIA_RECORD           ;break;
            case SDLK_MEDIA_FAST_FORWARD     :return KeyCode::MEDIA_FAST_FORWARD     ;break;
            case SDLK_MEDIA_REWIND           :return KeyCode::MEDIA_REWIND           ;break;
            case SDLK_MEDIA_NEXT_TRACK       :return KeyCode::MEDIA_NEXT_TRACK       ;break;
            case SDLK_MEDIA_PREVIOUS_TRACK   :return KeyCode::MEDIA_PREVIOUS_TRACK   ;break;
            case SDLK_MEDIA_STOP             :return KeyCode::MEDIA_STOP             ;break;
            case SDLK_MEDIA_EJECT            :return KeyCode::MEDIA_EJECT            ;break;
            case SDLK_MEDIA_PLAY_PAUSE       :return KeyCode::MEDIA_PLAY_PAUSE       ;break;
            case SDLK_MEDIA_SELECT           :return KeyCode::MEDIA_SELECT           ;break;
            case SDLK_AC_NEW                 :return KeyCode::AC_NEW                 ;break;
            case SDLK_AC_OPEN                :return KeyCode::AC_OPEN                ;break;
            case SDLK_AC_CLOSE               :return KeyCode::AC_CLOSE               ;break;
            case SDLK_AC_EXIT                :return KeyCode::AC_EXIT                ;break;
            case SDLK_AC_SAVE                :return KeyCode::AC_SAVE                ;break;
            case SDLK_AC_PRINT               :return KeyCode::AC_PRINT               ;break;
            case SDLK_AC_PROPERTIES          :return KeyCode::AC_PROPERTIES          ;break;
            case SDLK_AC_SEARCH              :return KeyCode::AC_SEARCH              ;break;
            case SDLK_AC_HOME                :return KeyCode::AC_HOME                ;break;
            case SDLK_AC_BACK                :return KeyCode::AC_BACK                ;break;
            case SDLK_AC_FORWARD             :return KeyCode::AC_FORWARD             ;break;
            case SDLK_AC_STOP                :return KeyCode::AC_STOP                ;break;
            case SDLK_AC_REFRESH             :return KeyCode::AC_REFRESH             ;break;
            case SDLK_AC_BOOKMARKS           :return KeyCode::AC_BOOKMARKS           ;break;
            case SDLK_SOFTLEFT               :return KeyCode::SOFTLEFT               ;break;
            case SDLK_SOFTRIGHT              :return KeyCode::SOFTRIGHT              ;break;
            case SDLK_CALL                   :return KeyCode::CALL                   ;break;
            case SDLK_ENDCALL                :return KeyCode::ENDCALL                ;break;
            default                          :return KeyCode::UNKNOWN;
        }
    }

    static MouseButtonCode SDL3toEngineMousebuttonCode(uint8_t button) {
        return (MouseButtonCode)(button - 1);
    }
}