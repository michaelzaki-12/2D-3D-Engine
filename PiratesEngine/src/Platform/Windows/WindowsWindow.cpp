#include "PEPCH.h"
#include "PiratesEngine/Core/Window.h"
#include "Platform/OpenGl/OpenGLContext.h"
#include "WindowsWindow.h"
#include "PiratesEngine/Events/KeyEvent.h"
#include "PiratesEngine/Events/MouseEvent.h"
#include "PiratesEngine/Events/Event.h"
#include "PiratesEngine/Events/ApplicationEvent.h"

namespace Pirates {
	static bool s_GLFWInitialized = false;


	static void GLFWErrorCallback(int error, const char* description) 
	{
		PR_CORE_ERROR("GLFW error ({0}) : {1}", description);
	}


	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		PR_PROFILE_FUNCTION();
		Init(props);
	}
	WindowsWindow::~WindowsWindow()
	{
		PR_PROFILE_FUNCTION();

		ShutDown();
	}
	void WindowsWindow::Init(const WindowProps& props)
	{
		PR_PROFILE_FUNCTION();
		m_Data.Title = props.Title;
		m_Data.Height = props.Height;
		m_Data.Width = props.Width;

		PR_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			PR_PROFILE_FUNCTION();
			int success = glfwInit();
			PR_CORE_ASSERT(success, "Could Not initalized GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);

			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);
		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;
			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyname)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keyname);
				data.EventCallback(event);

			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{

				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT: {
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
				
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						//PR_CORE_TRACE(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						//PR_CORE_TRACE(event);
						break;
					}
			}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			//PR_CORE_TRACE(event);
			data.EventCallback(event);

			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event((float)xpos, (float)ypos);
			//PR_CORE_TRACE(event);
			data.EventCallback(event);
			});
	}
	

	void WindowsWindow::ShutDown()
	{
		PR_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		PR_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}
	void WindowsWindow::SetVSync(bool enabled)
	{
		PR_PROFILE_FUNCTION();

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
	
	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}
