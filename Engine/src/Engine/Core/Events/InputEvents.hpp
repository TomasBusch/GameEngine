#pragma once

#include "Event.hpp"

#include <glm/glm.hpp>

namespace Engine::Input {
	
	//enum class KeyCode {
	///* Printable keys */
	//	SPACE              = 32,
	//	APOSTROPHE         = 39,  /* ' */
	//	COMMA              = 44,  /* , */
	//	MINUS              = 45,  /* - */
	//	PERIOD             = 46,  /* . */
	//	SLASH              = 47,  /* / */
	//	NUM_0              = 48,
	//	NUM_1              = 49,
	//	NUM_2              = 50,
	//	NUM_3              = 51,
	//	NUM_4              = 52,
	//	NUM_5              = 53,
	//	NUM_6              = 54,
	//	NUM_7              = 55,
	//	NUM_8              = 56,
	//	NUM_9              = 57,
	//	SEMICOLON          = 59,  /* ; */
	//	EQUAL              = 61,  /* = */
	//	A                  = 65,
	//	B                  = 66,
	//	C                  = 67,
	//	D                  = 68,
	//	E                  = 69,
	//	F                  = 70,
	//	G                  = 71,
	//	H                  = 72,
	//	I                  = 73,
	//	J                  = 74,
	//	K                  = 75,
	//	L                  = 76,
	//	M                  = 77,
	//	N                  = 78,
	//	O                  = 79,
	//	P                  = 80,
	//	Q                  = 81,
	//	R                  = 82,
	//	S                  = 83,
	//	T                  = 84,
	//	U                  = 85,
	//	V                  = 86,
	//	W                  = 87,
	//	X                  = 88,
	//	Y                  = 89,
	//	Z                  = 90,
	//	LEFT_BRACKET       = 91,  /* [ */
	//	BACKSLASH          = 92,  /* \ */
	//	RIGHT_BRACKET      = 93,  /* ] */
	//	GRAVE_ACCENT       = 96,  /* ` */
	//	WORLD_1            = 161, /* non-US #1 */
	//	WORLD_2            = 162, /* non-US #2 */
	//		
	///* Function keys */
	//	ESCAPE             = 256,
	//	ENTER              = 257,
	//	TAB                = 258,
	//	BACKSPACE          = 259,
	//	INSERT             = 260,
	//	DELETE             = 261,
	//	RIGHT              = 262,
	//	LEFT               = 263,
	//	DOWN               = 264,
	//	UP                 = 265,
	//	PAGE_UP            = 266,
	//	PAGE_DOWN          = 267,
	//	HOME               = 268,
	//	END                = 269,
	//	CAPS_LOCK          = 280,
	//	SCROLL_LOCK        = 281,
	//	NUM_LOCK           = 282,
	//	PRINT_SCREEN       = 283,
	//	PAUSE              = 284,
	//	F1                 = 290,
	//	F2                 = 291,
	//	F3                 = 292,
	//	F4                 = 293,
	//	F5                 = 294,
	//	F6                 = 295,
	//	F7                 = 296,
	//	F8                 = 297,
	//	F9                 = 298,
	//	F10                = 299,
	//	F11                = 300,
	//	F12                = 301,
	//	F13                = 302,
	//	F14                = 303,
	//	F15                = 304,
	//	F16                = 305,
	//	F17                = 306,
	//	F18                = 307,
	//	F19                = 308,
	//	F20                = 309,
	//	F21                = 310,
	//	F22                = 311,
	//	F23                = 312,
	//	F24                = 313,
	//	F25                = 314,
	//	KP_0               = 320,
	//	KP_1               = 321,
	//	KP_2               = 322,
	//	KP_3               = 323,
	//	KP_4               = 324,
	//	KP_5               = 325,
	//	KP_6               = 326,
	//	KP_7               = 327,
	//	KP_8               = 328,
	//	KP_9               = 329,
	//	KP_DECIMAL         = 330,
	//	KP_DIVIDE          = 331,
	//	KP_MULTIPLY        = 332,
	//	KP_SUBTRACT        = 333,
	//	KP_ADD             = 334,
	//	KP_ENTER           = 335,
	//	KP_EQUAL           = 336,
	//	LEFT_SHIFT         = 340,
	//	LEFT_CONTROL       = 341,
	//	LEFT_ALT           = 342,
	//	LEFT_SUPER         = 343,
	//	RIGHT_SHIFT        = 344,
	//	RIGHT_CONTROL      = 345,
	//	RIGHT_ALT          = 346,
	//	RIGHT_SUPER        = 347,
	//	MENU               = 348,
	//		
	//	LAST               = MENU
	//};

	enum KeyCode : int {
		/* Printable keys */
		SPACE = 32,
		APOSTROPHE = 39,  /* ' */
		COMMA = 44,  /* , */
		MINUS = 45,  /* - */
		PERIOD = 46,  /* . */
		SLASH = 47,  /* / */
		NUM_0 = 48,
		NUM_1 = 49,
		NUM_2 = 50,
		NUM_3 = 51,
		NUM_4 = 52,
		NUM_5 = 53,
		NUM_6 = 54,
		NUM_7 = 55,
		NUM_8 = 56,
		NUM_9 = 57,
		SEMICOLON = 59,  /* ; */
		EQUAL = 61,  /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91,  /* [ */
		BACKSLASH = 92,  /* \ */
		RIGHT_BRACKET = 93,  /* ] */
		GRAVE_ACCENT = 96,  /* ` */
		WORLD_1 = 161, /* non-US #1 */
		WORLD_2 = 162, /* non-US #2 */

		/* Function keys */
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP_0 = 320,
		KP_1 = 321,
		KP_2 = 322,
		KP_3 = 323,
		KP_4 = 324,
		KP_5 = 325,
		KP_6 = 326,
		KP_7 = 327,
		KP_8 = 328,
		KP_9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348,

		LAST = MENU
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

	enum MouseButtonCode {
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


	class KeyEvent : public Event {
	public:
		KeyCode Key;
		KeyAction Action;
		KeyModifiers Modifiers;
	public:
		KeyEvent(KeyCode kc, KeyAction action, KeyModifiers mod)
			:Key(kc), Action(action), Modifiers(mod), Event(Event::Priority::REAL_TIME)
		{}
		KeyEvent(KeyCode kc, KeyAction action, KeyModifiers mod, Event::Priority priority)
			:Key(kc), Action(action), Modifiers(mod), Event(priority)
		{}
	};

	class TextEvent : public Event {
	public:
		uint64_t UnicodeCode;
	public:
		TextEvent(uint64_t uc)
			:UnicodeCode(uc), Event(Event::Priority::LOW)
		{}
		TextEvent(uint64_t uc, Event::Priority priority)
			:UnicodeCode(uc), Event(priority)
		{}
	};

	class MouseButtonEvent : public Event {
	public:
		MouseButtonCode Button;
		KeyAction Action;
		KeyModifiers Modifiers;
	public:
		MouseButtonEvent(MouseButtonCode bc, KeyAction action, KeyModifiers mod)
			:Button(bc), Action(action), Modifiers(mod), Event(Event::Priority::REAL_TIME)
		{}
		MouseButtonEvent(MouseButtonCode bc, KeyAction action, KeyModifiers mod, Event::Priority priority)
			:Button(bc), Action(action), Modifiers(mod), Event(priority)
		{}
	};

	class MouseCursorEvent : public Event {
	public:
		glm::vec2 Position;
	public:
		MouseCursorEvent(glm::vec2 pos)
			:Position(pos), Event(Event::Priority::REAL_TIME)
		{}
		MouseCursorEvent(glm::vec2 pos, Event::Priority priority)
			:Position(pos), Event(priority)
		{}
	};

	class MouseCursorEnterEvent : public Event {
	public:
		bool Entered;
	public:
		MouseCursorEnterEvent(bool entered)
			:Entered(entered), Event(Event::Priority::REAL_TIME)
		{}
		MouseCursorEnterEvent(bool entered, Event::Priority priority)
			:Entered(entered), Event(priority)
		{}
	};

	class MouseScrollEvent : public Event {
	public:
		glm::vec2 Offset;
	public:
		MouseScrollEvent(glm::vec2 offset)
			:Offset(offset), Event(Event::Priority::REAL_TIME)
		{}
		MouseScrollEvent(glm::vec2 offset, Event::Priority priority)
			:Offset(offset), Event(priority)
		{}
	};
}