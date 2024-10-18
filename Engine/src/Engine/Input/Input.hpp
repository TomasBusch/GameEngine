#pragma once

#include "Engine/Core/Base.hpp"

namespace Engine::Input {

	enum class KeyCode {
		UNKNOWN = 0,
        RETURN,
        ESCAPE,
        BACKSPACE,
        TAB,
        SPACE,
        EXCLAIM,
        DBLAPOSTROPHE,
        HASH,
        DOLLAR,
        PERCENT,
        AMPERSAND,
        APOSTROPHE,
        LEFTPAREN,
        RIGHTPAREN,
        ASTERISK,
        PLUS,
        COMMA,
        MINUS,
        PERIOD,
        SLASH,
        NUM_0,
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        COLON,
        SEMICOLON,
        LESS,
        EQUALS,
        GREATER,
        QUESTION,
        AT,
        LEFTBRACKET,
        BACKSLASH,
        RIGHTBRACKET,
        CARET,
        UNDERSCORE,
        GRAVE,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LEFTBRACE,
        PIPE,
        RIGHTBRACE,
        TILDE,
        DELETE,
        PLUSMINUS,
        CAPSLOCK,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        PRINTSCREEN,
        SCROLLLOCK,
        PAUSE,
        INSERT,
        HOME,
        PAGEUP,
        END,
        PAGEDOWN,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        NUMLOCKCLEAR,
        KP_DIVIDE,
        KP_MULTIPLY,
        KP_MINUS,
        KP_PLUS,
        KP_ENTER,
        KP_1,
        KP_2,
        KP_3,
        KP_4,
        KP_5,
        KP_6,
        KP_7,
        KP_8,
        KP_9,
        KP_0,
        KP_PERIOD,
        APPLICATION,
        POWER,
        KP_EQUALS,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        EXECUTE,
        HELP,
        MENU,
        SELECT,
        STOP,
        AGAIN,
        UNDO,
        CUT,
        COPY,
        PASTE,
        FIND,
        MUTE,
        VOLUMEUP,
        VOLUMEDOWN,
        KP_COMMA,
        KP_EQUALSAS400,
        ALTERASE,
        SYSREQ,
        CANCEL,
        CLEAR,
        PRIOR,
        RETURN2,
        SEPARATOR,
        OUT,
        OPER,
        CLEARAGAIN,
        CRSEL,
        EXSEL,
        KP_00,
        KP_000,
        THOUSANDSSEPARATOR,
        DECIMALSEPARATOR,
        CURRENCYUNIT,
        CURRENCYSUBUNIT,
        KP_LEFTPAREN,
        KP_RIGHTPAREN,
        KP_LEFTBRACE,
        KP_RIGHTBRACE,
        KP_TAB,
        KP_BACKSPACE,
        KP_A,
        KP_B,
        KP_C,
        KP_D,
        KP_E,
        KP_F,
        KP_XOR,
        KP_POWER,
        KP_PERCENT,
        KP_LESS,
        KP_GREATER,
        KP_AMPERSAND,
        KP_DBLAMPERSAND,
        KP_VERTICALBAR,
        KP_DBLVERTICALBAR,
        KP_COLON,
        KP_HASH,
        KP_SPACE,
        KP_AT,
        KP_EXCLAM,
        KP_MEMSTORE,
        KP_MEMRECALL,
        KP_MEMCLEAR,
        KP_MEMADD,
        KP_MEMSUBTRACT,
        KP_MEMMULTIPLY,
        KP_MEMDIVIDE,
        KP_PLUSMINUS,
        KP_CLEAR,
        KP_CLEARENTRY,
        KP_BINARY,
        KP_OCTAL,
        KP_DECIMAL,
        KP_HEXADECIMAL,
        LCTRL,
        LSHIFT,
        LALT,
        LGUI,
        RCTRL,
        RSHIFT,
        RALT,
        RGUI,
        MODE,
        SLEEP,
        WAKE,
        CHANNEL_INCREMENT,
        CHANNEL_DECREMENT,
        MEDIA_PLAY,
        MEDIA_PAUSE,
        MEDIA_RECORD,
        MEDIA_FAST_FORWARD,
        MEDIA_REWIND,
        MEDIA_NEXT_TRACK,
        MEDIA_PREVIOUS_TRACK,
        MEDIA_STOP,
        MEDIA_EJECT,
        MEDIA_PLAY_PAUSE,
        MEDIA_SELECT,
        AC_NEW,
        AC_OPEN,
        AC_CLOSE,
        AC_EXIT,
        AC_SAVE,
        AC_PRINT,
        AC_PROPERTIES,
        AC_SEARCH,
        AC_HOME,
        AC_BACK,
        AC_FORWARD,
        AC_STOP,
        AC_REFRESH,
        AC_BOOKMARKS,
        SOFTLEFT,
        SOFTRIGHT,
        CALL,
        ENDCALL
	};

	enum class KeyAction {
		PRESSED,
		RELEASED,
		REPEAT
	};

	struct KeyModifiers {
		bool MOD_SHIFT = false;
		bool MOD_CONTROL = false;
		bool MOD_ALT = false;
		bool MOD_SUPER = false;
		bool MOD_CAPS_LOCK = false;
		bool MOD_NUM_LOCK = false;
	};

	enum class MouseButtonCode {
		BUTTON_1 = 0,
		BUTTON_2 = 1,
		BUTTON_3 = 2,
		BUTTON_4 = 3,
		BUTTON_5 = 4,
		BUTTON_6 = 5,
		BUTTON_7 = 6,
		BUTTON_8 = 7,
		BUTTON_LAST = BUTTON_8,
		BUTTON_LEFT = BUTTON_1,
		BUTTON_RIGHT = BUTTON_2,
		BUTTON_MIDDLE = BUTTON_3
	};

	using utf8_codepoint = char32_t;
	using scancode = int32_t;

	class PlatformInput {
	public:
        PlatformInput();
        ~PlatformInput();

        using KeyCallback = void(*)(KeyCode, KeyAction, KeyModifiers, scancode);
        using CharacterCallback = void(*)(utf8_codepoint);
        using MouseEnterCallback = void(*)(bool);
        using MousePositionCallback = void(*)(double, double, double, double);
        using ScrollCallback = void(*)(double, double);
        using MouseButtonCallback = void(*)(MouseButtonCode, KeyAction);

        struct InputCallbacks {
            KeyCallback	            KeyCallback = nullptr;
            CharacterCallback       CharCallback = nullptr;
            MouseEnterCallback      MouseEnterCallback = nullptr;
            MousePositionCallback   MousePosCallback = nullptr;
            ScrollCallback          ScrollCallback = nullptr;
            MouseButtonCallback	    MouseButtonCallback = nullptr;
        };

        void Init(void *init_data);

        void StartTextInput();
        void StopTextInput();


        enum class CursorState {
            ENABLED,
            DISABLED,
            HIDDEN,
            CAPTURED
        };
        void SetCursor(CursorState state);

        void SetKeyCallback(KeyCallback cb);
        void SetCharCallback(CharacterCallback cb);
        void SetMouseEnterCallback(MouseEnterCallback cb);
        void SetMousePosCallback(MousePositionCallback cb);
        void SetScrollCallback(ScrollCallback cb);
        void SetMouseButtonCallback(MouseButtonCallback cb);
	protected:
		InputCallbacks m_InputCallbacks;
        void* m_WindowHandle = nullptr;
	};
}