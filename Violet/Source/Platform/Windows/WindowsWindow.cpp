/////////////////
///
/// WindowsWindow.h
/// Violet McAllister
/// July 11th, 2022
/// Updated: July 11th, 2022
///
/// Using the generalized Window class we create
/// a WindowsWindow implementation for a Windows
/// system using GLFW.
///
/////////////////

#include "vtpch.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Violet/Events/ApplicationEvent.h"
#include "Violet/Events/KeyEvent.h"
#include "Violet/Events/MouseEvent.h"

namespace Violet
{
	/**
	 * @brief This exists so that we know when we've
	 * already initialized GLFW and do not have to
	 * do it again, causing issues.
	 */
	static bool s_GLFWInitialized = false;

	/**
	 * @brief Run whenever an error is caught by GLFW. Gives information about
	 * the error and why the error occured.
	 * @param p_Error The error code.
	 * @param p_Description The description of the error.
	 */
	static void GLFWErrorCallback(int p_Error, const char* p_Description)
	{
		VT_CORE_ERROR("GLFW Error ({0}): {1}", p_Error, p_Description);
	}

	/**
	 * @brief Allows the user to create a Window for the Windows
	 * system without specifically referencing Windows.
	 * @param p_Properties The window properties (title, width, height).
	 * @returns The windows window, not implemented for Windows.
	 */
	Scope<Window> Window::Create(const WindowProperties& p_Properties)
	{
		return CreateScope<WindowsWindow>(p_Properties);
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

			// Set error callback that was defined earlier.
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// Create the window.
		// When specifying fullscreen mode, you use the monitor, for windowed, use nullptr.
		// nullptr also for share sinec we aren't sharing resources to other monitors.
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		
		// Create & Initialize Context
		m_Context = CreateRef<OpenGLContext>(m_Window);
		m_Context->Init();

		// Sets a User Pointer containing data for the window, not modified by GLFW.
		glfwSetWindowUserPointer(m_Window, &m_Data);
		// Activates Vertical Sync.
		SetVSync(true);

		/// SET GLFW CALLBACKS \\\

		/**
		 * @brief Updates the internal information about the window size in OpenGL when the window
		 * is resized.
		 * @param p_Window The window being resized.
		 * @param p_Width The width being resized to.
		 * @param p_Height The height being resized to.
		 */
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* p_Window, int p_Width, int p_Height)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);
			data.Width = p_Width;
			data.Height = p_Height;

			// Creates a Violet Event and sets it.
			WindowResizeEvent e(p_Width, p_Height);
			data.EventCallback(e);
		});

		/**
		 * @brief Closes the window when the close button is pressed.
		 * @param p_Window The window being closed.
		 */
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* p_Window)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event and sets it.
			WindowCloseEvent e;
			data.EventCallback(e);
		});

		/**
		 * @brief Runs when any key event is executed.
		 * @param p_Window The window being interacted with.
		 * @param p_Key The keycode of the key event.
		 * @param p_ScanCode Specified system-specific scancode of the key.
		 * @param p_Action The type of action of the event (press, release, repeat).
		 * @param p_Mods How the key is being modified (ctrl+key, etc.).
		 */
		glfwSetKeyCallback(m_Window, [](GLFWwindow* p_Window, int p_Key, int p_ScanCode, int p_Action, int p_Mods)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event depending on p_Action
			switch (p_Action)
			{
				// KeyPressed Action
				case GLFW_PRESS:
				{
					KeyPressedEvent e(p_Key, 0);
					data.EventCallback(e);
					break;
				}
				// KeyReleased Action
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(p_Key);
					data.EventCallback(e);
					break;
				}
				// KeyPressed Repeat Action
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(p_Key, 1);
					data.EventCallback(e);
					break;
				}
			}
		});

		/**
		 * @brief Runs when keys are typed.
		 * @param p_Window The window being closed.
		 * @param p_KeyCode The keycode being typed.
		 */
		glfwSetCharCallback(m_Window, [](GLFWwindow* p_Window, unsigned int p_KeyCode)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event and sets it.
			KeyTypedEvent e(p_KeyCode);
			data.EventCallback(e);
		});

		/**
		 * @brief Runs when any mouse event is executed.
		 * @param p_Window The window being interacted with.
		 * @param p_Button The mousecode of the mouse event.
		 * @param p_Action The type of action of the event (press, release).
		 * @param p_Mods How the key is being modified (ctrl+click, etc.).
		 */
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* p_Window, int p_Button, int p_Action, int p_Mods)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event depending on p_Action
			switch (p_Action)
			{
				// MousePressed Action
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(p_Button);
					data.EventCallback(e);
					break;
				}
				// KeyReleased Action
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(p_Button);
					data.EventCallback(e);
					break;
				}
			}
		});

		/**
		 * @brief Updates the internal information about the scroll position of the scroll wheel.
		 * @param p_Window The window being resized.
		 * @param p_XOffset The updated scroll position.
		 * @param p_Height The updated scroll position.
		 */
		glfwSetScrollCallback(m_Window, [](GLFWwindow* p_Window, double p_XOffset, double p_YOffset)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event and sets it.
			MouseScrolledEvent e((float)p_XOffset, (float)p_YOffset);
			data.EventCallback(e);
		});

		/**
		 * @brief Updates the internal information about the mouse position.
		 * @param p_Window The window being resized.
		 * @param p_XPos The updated mouse position.
		 * @param p_YPos The updated mouse position.
		 */
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* p_Window, double p_XPos, double p_YPos)
		{
			// Gets the window data based on the window pointer.
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_Window);

			// Creates a Violet Event and sets it.
			MouseMovedEvent e((float)p_XPos, (float)p_YPos);
			data.EventCallback(e);
		});
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
		
		// Context Swaps Buffers.
		m_Context->SwapBuffers();
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