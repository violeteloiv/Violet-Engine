/////////////////
///
/// KeyCodes.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
///
/// List of KeyCodes from GLFW.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_KEY_CODES_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_KEY_CODES_H_INCLUDED__

namespace Violet
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

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

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
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

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& p_OutStream, KeyCode p_KeyCode)
	{
		p_OutStream << static_cast<int32_t>(p_KeyCode);
		return p_OutStream;
	}
}

#define VT_KEY_SPACE           ::Violet::Key::Space
#define VT_KEY_APOSTROPHE      ::Violet::Key::Apostrophe    /* ' */
#define VT_KEY_COMMA           ::Violet::Key::Comma         /* , */
#define VT_KEY_MINUS           ::Violet::Key::Minus         /* - */
#define VT_KEY_PERIOD          ::Violet::Key::Period        /* . */
#define VT_KEY_SLASH           ::Violet::Key::Slash         /* / */
#define VT_KEY_0               ::Violet::Key::D0
#define VT_KEY_1               ::Violet::Key::D1
#define VT_KEY_2               ::Violet::Key::D2
#define VT_KEY_3               ::Violet::Key::D3
#define VT_KEY_4               ::Violet::Key::D4
#define VT_KEY_5               ::Violet::Key::D5
#define VT_KEY_6               ::Violet::Key::D6
#define VT_KEY_7               ::Violet::Key::D7
#define VT_KEY_8               ::Violet::Key::D8
#define VT_KEY_9               ::Violet::Key::D9
#define VT_KEY_SEMICOLON       ::Violet::Key::Semicolon     /* ; */
#define VT_KEY_EQUAL           ::Violet::Key::Equal         /* = */
#define VT_KEY_A               ::Violet::Key::A
#define VT_KEY_B               ::Violet::Key::B
#define VT_KEY_C               ::Violet::Key::C
#define VT_KEY_D               ::Violet::Key::D
#define VT_KEY_E               ::Violet::Key::E
#define VT_KEY_F               ::Violet::Key::F
#define VT_KEY_G               ::Violet::Key::G
#define VT_KEY_H               ::Violet::Key::H
#define VT_KEY_I               ::Violet::Key::I
#define VT_KEY_J               ::Violet::Key::J
#define VT_KEY_K               ::Violet::Key::K
#define VT_KEY_L               ::Violet::Key::L
#define VT_KEY_M               ::Violet::Key::M
#define VT_KEY_N               ::Violet::Key::N
#define VT_KEY_O               ::Violet::Key::O
#define VT_KEY_P               ::Violet::Key::P
#define VT_KEY_Q               ::Violet::Key::Q
#define VT_KEY_R               ::Violet::Key::R
#define VT_KEY_S               ::Violet::Key::S
#define VT_KEY_T               ::Violet::Key::T
#define VT_KEY_U               ::Violet::Key::U
#define VT_KEY_V               ::Violet::Key::V
#define VT_KEY_W               ::Violet::Key::W
#define VT_KEY_X               ::Violet::Key::X
#define VT_KEY_Y               ::Violet::Key::Y
#define VT_KEY_Z               ::Violet::Key::Z
#define VT_KEY_LEFT_BRACKET    ::Violet::Key::LeftBracket   /* [ */
#define VT_KEY_BACKSLASH       ::Violet::Key::Backslash     /* \ */
#define VT_KEY_RIGHT_BRACKET   ::Violet::Key::RightBracket  /* ] */
#define VT_KEY_GRAVE_ACCENT    ::Violet::Key::GraveAccent   /* ` */
#define VT_KEY_WORLD_1         ::Violet::Key::World1        /* non-US #1 */
#define VT_KEY_WORLD_2         ::Violet::Key::World2        /* non-US #2 */

/* Function keys */
#define VT_KEY_ESCAPE          ::Violet::Key::Escape
#define VT_KEY_ENTER           ::Violet::Key::Enter
#define VT_KEY_TAB             ::Violet::Key::Tab
#define VT_KEY_BACKSPACE       ::Violet::Key::Backspace
#define VT_KEY_INSERT          ::Violet::Key::Insert
#define VT_KEY_DELETE          ::Violet::Key::Delete
#define VT_KEY_RIGHT           ::Violet::Key::Right
#define VT_KEY_LEFT            ::Violet::Key::Left
#define VT_KEY_DOWN            ::Violet::Key::Down
#define VT_KEY_UP              ::Violet::Key::Up
#define VT_KEY_PAGE_UP         ::Violet::Key::PageUp
#define VT_KEY_PAGE_DOWN       ::Violet::Key::PageDown
#define VT_KEY_HOME            ::Violet::Key::Home
#define VT_KEY_END             ::Violet::Key::End
#define VT_KEY_CAPS_LOCK       ::Violet::Key::CapsLock
#define VT_KEY_SCROLL_LOCK     ::Violet::Key::ScrollLock
#define VT_KEY_NUM_LOCK        ::Violet::Key::NumLock
#define VT_KEY_PRINT_SCREEN    ::Violet::Key::PrintScreen
#define VT_KEY_PAUSE           ::Violet::Key::Pause
#define VT_KEY_F1              ::Violet::Key::F1
#define VT_KEY_F2              ::Violet::Key::F2
#define VT_KEY_F3              ::Violet::Key::F3
#define VT_KEY_F4              ::Violet::Key::F4
#define VT_KEY_F5              ::Violet::Key::F5
#define VT_KEY_F6              ::Violet::Key::F6
#define VT_KEY_F7              ::Violet::Key::F7
#define VT_KEY_F8              ::Violet::Key::F8
#define VT_KEY_F9              ::Violet::Key::F9
#define VT_KEY_F10             ::Violet::Key::F10
#define VT_KEY_F11             ::Violet::Key::F11
#define VT_KEY_F12             ::Violet::Key::F12
#define VT_KEY_F13             ::Violet::Key::F13
#define VT_KEY_F14             ::Violet::Key::F14
#define VT_KEY_F15             ::Violet::Key::F15
#define VT_KEY_F16             ::Violet::Key::F16
#define VT_KEY_F17             ::Violet::Key::F17
#define VT_KEY_F18             ::Violet::Key::F18
#define VT_KEY_F19             ::Violet::Key::F19
#define VT_KEY_F20             ::Violet::Key::F20
#define VT_KEY_F21             ::Violet::Key::F21
#define VT_KEY_F22             ::Violet::Key::F22
#define VT_KEY_F23             ::Violet::Key::F23
#define VT_KEY_F24             ::Violet::Key::F24
#define VT_KEY_F25             ::Violet::Key::F25

/* Keypad */
#define VT_KEY_KP_0            ::Violet::Key::KP0
#define VT_KEY_KP_1            ::Violet::Key::KP1
#define VT_KEY_KP_2            ::Violet::Key::KP2
#define VT_KEY_KP_3            ::Violet::Key::KP3
#define VT_KEY_KP_4            ::Violet::Key::KP4
#define VT_KEY_KP_5            ::Violet::Key::KP5
#define VT_KEY_KP_6            ::Violet::Key::KP6
#define VT_KEY_KP_7            ::Violet::Key::KP7
#define VT_KEY_KP_8            ::Violet::Key::KP8
#define VT_KEY_KP_9            ::Violet::Key::KP9
#define VT_KEY_KP_DECIMAL      ::Violet::Key::KPDecimal
#define VT_KEY_KP_DIVIDE       ::Violet::Key::KPDivide
#define VT_KEY_KP_MULTIPLY     ::Violet::Key::KPMultiply
#define VT_KEY_KP_SUBTRACT     ::Violet::Key::KPSubtract
#define VT_KEY_KP_ADD          ::Violet::Key::KPAdd
#define VT_KEY_KP_ENTER        ::Violet::Key::KPEnter
#define VT_KEY_KP_EQUAL        ::Violet::Key::KPEqual
					
#define VT_KEY_LEFT_SHIFT      ::Violet::Key::LeftShift
#define VT_KEY_LEFT_CONTROL    ::Violet::Key::LeftControl
#define VT_KEY_LEFT_ALT        ::Violet::Key::LeftAlt
#define VT_KEY_LEFT_SUPER      ::Violet::Key::LeftSuper
#define VT_KEY_RIGHT_SHIFT     ::Violet::Key::RightShift
#define VT_KEY_RIGHT_CONTROL   ::Violet::Key::RightControl
#define VT_KEY_RIGHT_ALT       ::Violet::Key::RightAlt
#define VT_KEY_RIGHT_SUPER     ::Violet::Key::RightSuper
#define VT_KEY_MENU            ::Violet::Key::Menu

#endif // __VIOLET_ENGINE_CORE_KEY_CODES_H_INCLUDED__