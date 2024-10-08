#pragma once

#include "Engine/Core/Base.hpp"

namespace Engine::Input {

	//enum class KeyCode : int {
	//	/* Printable keys */
	//	UNKOWN = 0,
	//	SPACE = 32,
	//	APOSTROPHE = 39,  /* ' */
	//	COMMA = 44,  /* , */
	//	MINUS = 45,  /* - */
	//	PERIOD = 46,  /* . */
	//	SLASH = 47,  /* / */
	//	NUM_0 = 48,
	//	NUM_1 = 49,
	//	NUM_2 = 50,
	//	NUM_3 = 51,
	//	NUM_4 = 52,
	//	NUM_5 = 53,
	//	NUM_6 = 54,
	//	NUM_7 = 55,
	//	NUM_8 = 56,
	//	NUM_9 = 57,
	//	SEMICOLON = 59,  /* ; */
	//	EQUAL = 61,  /* = */
	//	A = 65,
	//	B = 66,
	//	C = 67,
	//	D = 68,
	//	E = 69,
	//	F = 70,
	//	G = 71,
	//	H = 72,
	//	I = 73,
	//	J = 74,
	//	K = 75,
	//	L = 76,
	//	M = 77,
	//	N = 78,
	//	O = 79,
	//	P = 80,
	//	Q = 81,
	//	R = 82,
	//	S = 83,
	//	T = 84,
	//	U = 85,
	//	V = 86,
	//	W = 87,
	//	X = 88,
	//	Y = 89,
	//	Z = 90,
	//	LEFT_BRACKET = 91,  /* [ */
	//	BACKSLASH = 92,  /* \ */
	//	RIGHT_BRACKET = 93,  /* ] */
	//	GRAVE_ACCENT = 96,  /* ` */
	//	WORLD_1 = 161, /* non-US #1 */
	//	WORLD_2 = 162, /* non-US #2 */

	//	/* Function keys */
	//	ESCAPE = 256,
	//	ENTER = 257,
	//	TAB = 258,
	//	BACKSPACE = 259,
	//	INSERT = 260,
	//	DELETE = 261,
	//	RIGHT = 262,
	//	LEFT = 263,
	//	DOWN = 264,
	//	UP = 265,
	//	PAGE_UP = 266,
	//	PAGE_DOWN = 267,
	//	HOME = 268,
	//	END = 269,
	//	CAPS_LOCK = 280,
	//	SCROLL_LOCK = 281,
	//	NUM_LOCK = 282,
	//	PRINT_SCREEN = 283,
	//	PAUSE = 284,
	//	F1 = 290,
	//	F2 = 291,
	//	F3 = 292,
	//	F4 = 293,
	//	F5 = 294,
	//	F6 = 295,
	//	F7 = 296,
	//	F8 = 297,
	//	F9 = 298,
	//	F10 = 299,
	//	F11 = 300,
	//	F12 = 301,
	//	F13 = 302,
	//	F14 = 303,
	//	F15 = 304,
	//	F16 = 305,
	//	F17 = 306,
	//	F18 = 307,
	//	F19 = 308,
	//	F20 = 309,
	//	F21 = 310,
	//	F22 = 311,
	//	F23 = 312,
	//	F24 = 313,
	//	F25 = 314,
	//	KP_0 = 320,
	//	KP_1 = 321,
	//	KP_2 = 322,
	//	KP_3 = 323,
	//	KP_4 = 324,
	//	KP_5 = 325,
	//	KP_6 = 326,
	//	KP_7 = 327,
	//	KP_8 = 328,
	//	KP_9 = 329,
	//	KP_DECIMAL = 330,
	//	KP_DIVIDE = 331,
	//	KP_MULTIPLY = 332,
	//	KP_SUBTRACT = 333,
	//	KP_ADD = 334,
	//	KP_ENTER = 335,
	//	KP_EQUAL = 336,
	//	LEFT_SHIFT = 340,
	//	LEFT_CONTROL = 341,
	//	LEFT_ALT = 342,
	//	LEFT_SUPER = 343,
	//	RIGHT_SHIFT = 344,
	//	RIGHT_CONTROL = 345,
	//	RIGHT_ALT = 346,
	//	RIGHT_SUPER = 347,
	//	MENU = 348,

	//	LAST = MENU
	//};

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
		PlatformInput()
			:m_InputCallbacks(InputCallbacks())
		{}
		~PlatformInput() = default;

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

        virtual void Init(void *init_data) = 0;

        virtual void StartTextInput() = 0;
        virtual void StopTextInput() = 0;


        enum class CursorState {
            ENABLED,
            DISABLED,
            HIDDEN,
            CAPTURED
        };
        virtual void SetCursor(CursorState state) = 0;

        virtual void SetKeyCallback(KeyCallback cb) = 0;
        virtual void SetCharCallback(CharacterCallback cb) = 0;
        virtual void SetMouseEnterCallback(MouseEnterCallback cb) = 0;
        virtual void SetMousePosCallback(MousePositionCallback cb) = 0;
        virtual void SetScrollCallback(ScrollCallback cb) = 0;
        virtual void SetMouseButtonCallback(MouseButtonCallback cb) = 0;
	protected:
		InputCallbacks m_InputCallbacks;
        void* m_WindowHandle = nullptr;
	};
}