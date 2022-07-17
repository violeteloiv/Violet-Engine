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
#include <iomanip>
#include <string>
#include <thread>

namespace Violet
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	/**
	 * @brief Contains the name, start, end, and thread ID of
	 * a profile element.
	 */
	struct ProfileResult
	{
		std::string Name;
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;
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
			: m_CurrentSession(nullptr)
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
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					VT_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", p_Name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}

			m_OutputStream.open(p_Filepath);

			if (m_OutputStream.is_open()) {
				m_CurrentSession = new InstrumentationSession({ p_Name });
				WriteHeader();
			}
			else {
				if (Log::GetCoreLogger()) { // Edge case: BeginSession() might be before Log::Init()
					VT_CORE_ERROR("Instrumentor could not open results file '{0}'.", p_Filepath);
				}
			}
		}

		/**
		 * @brief Ends an instrumentation session. 
		 */
		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		/**
		 * @brief Writes profile information into the instrumentation
		 * file.
		 * @param p_Result The instrumentation file.
		 */
		void WriteProfile(const ProfileResult& p_Result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (p_Result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << p_Result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << p_Result.ThreadID << ",";
			json << "\"ts\":" << p_Result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) {
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
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
	private: // Helper
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

		/**
		 * @brief Ends the session internally. NOTE: You
		 * must own lock on m_Mutex before calling this.
		 */
		void InternalEndSession() {
			if (m_CurrentSession) {
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}
	private: // Private Member Variables
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;
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
			m_StartTimepoint = std::chrono::steady_clock::now();
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
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}
	private: // Private Member Variables
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};

	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define VT_PROFILE 1
#if VT_PROFILE
	// Resolve which function signature macro will be used. Note that this only
		// is resolved when the (pre)compiler starts, so the syntax highlighting
		// could mark the wrong one in your editor!
	#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__)
		#define VT_FUNC_SIG __PRETTY_FUNCTION__
	#elif defined(__DMC__) && (__DMC__ >= 0x810)
		#define VT_FUNC_SIG __PRETTY_FUNCTION__
	#elif (defined(__FUNCSIG__) || (_MSC_VER))
		#define VT_FUNC_SIG __FUNCSIG__
	#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
		#define VT_FUNC_SIG __FUNCTION__
	#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
		#define VT_FUNC_SIG __FUNC__
	#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
		#define VT_FUNC_SIG __func__
	#elif defined(__cplusplus) && (__cplusplus >= 201103)
		#define VT_FUNC_SIG __func__
	#else
		#define VT_FUNC_SIG "HZ_FUNC_SIG unknown!"
	#endif

	#define VT_PROFILE_BEGIN_SESSION(name, filepath) ::Violet::Instrumentor::Get().BeginSession(name, filepath)
	#define VT_PROFILE_END_SESSION() ::Violet::Instrumentor::Get().EndSession()
	#define VT_PROFILE_SCOPE(name) constexpr auto fixedName = ::Violet::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
									::Violet::InstrumentationTimer timer##__LINE__(fixedName.Data)
	#define VT_PROFILE_FUNCTION() VT_PROFILE_SCOPE(VT_FUNC_SIG)
#else
	#define VT_PROFILE_BEGIN_SESSION(name, filepath)
	#define VT_PROFILE_END_SESSION()
	#define VT_PROFILE_SCOPE(name)
	#define VT_PROFILE_FUNCTION()
#endif 

#endif // __VIOLET_ENGINE_DEBUG_INSTRUMENTOR_H_INCLUDED__