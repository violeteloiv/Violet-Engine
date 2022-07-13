/////////////////
///
/// Timestep.h
/// Violet McAllister
/// July 12th, 2022
///
/// Defines how much time has
/// elapsed in a frame.
///
/////////////////

#ifndef __VIOLET_ENGINE_CORE_TIMESTEP_H_INCLUDED__
#define __VIOLET_ENGINE_CORE_TIMESTEP_H_INCLUDED__

namespace Violet
{
	class Timestep
	{
	public: // Constructors
		/**
		 * @brief Constructs a Timestep object.
		 * @param p_Time The current program time.
		 */
		Timestep(float p_Time = 0.0f)
			: m_Time(p_Time)
		{

		}
	public: // Conversion
		/**
		 * @brief Converts Timestep to float.
		 * @returns m_Time.
		 */
		operator float() const { return m_Time; }
	public: // Getters
		/**
		 * @brief Gets the time in seconds.
		 * @returns The time in seconds.
		 */
		float GetSeconds() const { return m_Time; }

		/**
		 * @brief Gets the time in milliseconds.
		 * @returns The time in milliseconds.
		 */
		float GetMilliseconds() const { return m_Time * 1000.0f; }
	private: // Private Member Variables
		float m_Time;
	};
}

#endif // __VIOLET_ENGINE_CORE_TIMESTEP_H_INCLUDED__