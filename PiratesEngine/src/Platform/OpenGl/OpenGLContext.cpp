#include "PEPCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include "glad/glad.h"
namespace Pirates
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowhandle) : m_WindowHandle(windowhandle)
	{
		PR_CORE_ASSERT(m_WindowHandle, "WindowHandle is not assert");
	}
	void OpenGLContext::Init()
	{
		PR_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PR_CORE_ASSERT(status, "Failed to initize glad";)

		PR_CORE_INFO(glGetString(GL_VENDOR));
		PR_CORE_INFO(glGetString(GL_RENDERER));
		PR_CORE_INFO(glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		PR_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}
}