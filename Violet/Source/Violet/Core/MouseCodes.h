/////////////////
///
/// MouseButtonCodes.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 23rd, 2022
///
/// List of MouseCodes from GLFW.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__

namespace Violet
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		/**
		 * @brief List of mouse codes from
		 * GLFW.
		 */
		enum : MouseCode
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
		};
	}
}

#endif // __VIOLET_ENGINE_CORE_MOUSE_BUTTON_CODES_H_INCLUDED__
