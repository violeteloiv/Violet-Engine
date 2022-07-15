/////////////////
///
/// Instrumentor.h
/// Violet McAllister
/// July 15th, 2022
/// 
/// Instrumentation information and
/// implementations.
///
/////////////////

#ifndef __VIOLET_ENGINE_DEBUG_INSTRUMENTOR_H_INCLUDED__
#define __VIOLET_ENGINE_DEBUG_INSTRUMENTOR_H_INCLUDED__

#include <algorithm>
#include <chrono>
#include <fstream>
#include <string>
#include <thread>

namespace Violet
{
	/**
	 * @brief Contains the name, start, end, and thread ID of
	 * a profile element.
	 */
	struct ProfileResult
	{
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	/**
	 * @brief Contains an instrumentation session.
	 */
	struct InstrumentationSession
	{
		std::string Name;
	};

	/**
	 * @brief Responsible for writing the timer
	 * information to a file for use in determining
	 * API speeds.
	 */
	class Instrumentor
	{
	public: // Constructor
		/**
		 * @brief Constructs an Instrumentor object. 
		 */
		Instrumentor()
			: m_CurrentSession(nullptr), m_ProfileCount(0)
		{

		}
	public: // Main Functionality
		/**
		 * @brief Begins an instrumentation session.
		 * @param p_Name The name of the session.
		 * @param p_Filepath The path to the results file.
		 */
		void BeginSession(const std::string& p_Name, const std::string& p_Filepath = "results.json")
		{
			m_OutputStream.open(p_Filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{ p_Name };
		}

		/**
		 * @brief Ends an instrumentation session. 
		 */
		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		/**
		 * @brief Writes profile information into the instrumentation
		 * file.
		 * @param p_Result The instrumentation file.
		 */
		void WriteProfile(const ProfileResult& p_Result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = p_Result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (p_Result.End - p_Result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << p_Result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << p_Result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}
	public: // Helper
		/**
		 * @brief Writes the JSON file header. 
		 */
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		/**
		 * @brief Writes the JSON file footer. 
		 */
		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}
	public: // Getter
		/**
		 * @brief Gets the instrumentor instance.
		 * @returns The instrumentor instance.
		 */
		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}
	private: // Private Member Variables
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;
	};

	class InstrumentationTimer
	{
	public: // Constructors & Deconstructors
		/**
		 * @brief Constructs an Instrumentation Timer with a name.
		 * @param p_Name The name of the timer.
		 */
		InstrumentationTimer(const char* p_Name)
			: m_Name(p_Name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		/**
		 * @brief Deconstructs an Instrumentation Timer. 
		 */
		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}
	public: // Main Functionality
		/**
		 * @brief Stops the instrumentation timer and defines the
		 * profile result.
		 */
		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}
	private: // Private Member Variables
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define VT_PROFILE 1
#if VT_PROFILE
	#define VT_PROFILE_BEGIN_SESSION(name, filepath) ::Violet::Instrumentor::Get().BeginSession(name, filepath)
	#define VT_PROFILE_END_SESSION() ::Violet::Instrumentor::Get().EndSession()
	#define VT_PROFILE_SCOPE(name) ::Violet::InstrumentationTimer timer##__LINE__(name);
	#define VT_PROFILE_FUNCTION() VT_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define VT_PROFILE_BEGIN_SESSION(name, filepath)
	#define VT_PROFILE_END_SESSION()
	#define VT_PROFILE_SCOPE(name)
	#define VT_PROFILE_FUNCTION()
#endif 

#endif // __VIOLET_ENGINE_DEBUG_INSTRUMENTOR_H_INCLUDED__