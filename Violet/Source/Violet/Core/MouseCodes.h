/////////////////
///
/// MouseButtonCodes.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 15th, 2022
///
/// List of MouseCodes from GLFW.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__

namespace Violet
{
	/**
	 * @brief A list of codes from GLFW. 
	 */
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& p_OutStream, MouseCode p_MouseCode)
	{
		p_OutStream << static_cast<int32_t>(p_MouseCode);
		return p_OutStream;
	}
}

#define VT_MOUSE_BUTTON_0      ::Violet::Mouse::Button0
#define VT_MOUSE_BUTTON_1      ::Violet::Mouse::Button1
#define VT_MOUSE_BUTTON_2      ::Violet::Mouse::Button2
#define VT_MOUSE_BUTTON_3      ::Violet::Mouse::Button3
#define VT_MOUSE_BUTTON_4      ::Violet::Mouse::Button4
#define VT_MOUSE_BUTTON_5      ::Violet::Mouse::Button5
#define VT_MOUSE_BUTTON_6      ::Violet::Mouse::Button6
#define VT_MOUSE_BUTTON_7      ::Violet::Mouse::Button7
#define VT_MOUSE_BUTTON_LAST   ::Violet::Mouse::ButtonLast
#define VT_MOUSE_BUTTON_LEFT   ::Violet::Mouse::ButtonLeft
#define VT_MOUSE_BUTTON_RIGHT  ::Violet::Mouse::ButtonRight
#define VT_MOUSE_BUTTON_MIDDLE ::Violet::Mouse::ButtonMiddle

#endif // __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__