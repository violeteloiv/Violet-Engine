/////////////////
///
/// WindowsWindow.h
/// Violet McAllister
/// July 1st, 2022
///
/// Using the generalized Window class we create
/// a WindowsWindow implementation for a Windows
/// system using GLFW.
///
/////////////////

#include "vtpch.h"

#include "Platform/Windows/WindowsWindow.h"

namespace Violet
{
	/**
	 * @brief This exists so that we know when we've
	 * already initialized GLFW and do not have to
	 * do it again, causing issues.
	 */
	static bool s_GLFWInitialized = false;

	/**
	 * @brief Allows the user to create a Window for the Windows
	 * system without specifically referencing Windows.
	 * @param p_Properties The window properties (title, width, height).
	 * @returns The windows window, not implemented for Windows.
	 */
	Window* Window::Create(const WindowProperties& p_Properties)
	{
		return new WindowsWindow(p_Properties);
	}

	/**
	 * @brief Constructs a WindowsWindow object.
	 * @param p_Properties The window properties (title, width, height).
	 */
	WindowsWindow::WindowsWindow(const WindowProperties& p_Properties)
	{
		Init(p_Properties);
	}

	/**
	 * @brief Deconstructs a WindowsWindow object.
	 */
	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	/**
	 * @brief Initialized a window using GLFW.
	 * @param p_Properties The window properties (title, width, height).
	 */
	void WindowsWindow::Init(const WindowProperties& p_Properties)
	{
		m_Data.Title = p_Properties.Title;
		m_Data.Width = p_Properties.Width;
		m_Data.Height = p_Properties.Height;

		VT_CORE_INFO("Creating Window {0} ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		// Sanity check to make sure GLFW isn't already initialized.
		if (!s_GLFWInitialized)
		{
			// Initialize GLFW :)
			int success = glfwInit();
			VT_CORE_ASSERT(success, "[GLFW ERROR] Could Not Initialize GLFW!");

			s_GLFWInitialized = true;
		}

		// Create the window.
		// When specifying fullscreen mode, you use the monitor, for windowed, use nullptr.
		// nullptr also for share sinec we aren't sharing resources to other monitors.
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		// Tells GLFW which window context to use for displaying pixel data.
		glfwMakeContextCurrent(m_Window);
		// Sets a User Pointer containing data for the window, not modified by GLFW.
		glfwSetWindowUserPointer(m_Window, &m_Data);
		// Activates Vertical Sync.
		SetVSync(true);
	}

	/**
	 * @brief Destroys a window when the program ends. 
	 */
	void WindowsWindow::Shutdown()
	{
		// GLFW destroys the window and all data associated with it.
		glfwDestroyWindow(m_Window);
	}

	/**
	 * @brief Runs whenever the application updates.
	 */
	void WindowsWindow::OnUpdate()
	{
		// GLFW processes the events that it is listening for and sets flags
		// saying whether or not those events have been triggered.
		glfwPollEvents();
		// GLFW swaps the framebuffers from front to back allowing rendering to
		// be smooth. Pixels are rendered to a back buffer before displayed on
		// the screen. This switches the buffer.
		glfwSwapBuffers(m_Window);
	}

	/**
	 * @brief Sets The Vertical Sync.
	 * @param p_Enabled Whether to enable Vertical Sync or not.
	 */
	void WindowsWindow::SetVSync(bool p_Enabled)
	{
		// When VSync is enabled, the screen updates once before swapping buffers,
		// allowing the functionality shown in OnUpdate for glfwSwapBuffers to occur.
		// When VSync is disabled, pixels are rendered as the data is sent, meaning that
		// a screen may begin displaying before all pixels are loaded.

		if (p_Enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = p_Enabled;
	}

	/**
	 * @brief Gets if Vertical Sync is enabled.
	 * @returns Whether or not Vertical Sync is enabled.
	 */
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}