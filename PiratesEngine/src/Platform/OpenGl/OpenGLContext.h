#pragma once
#include "PiratesEngine/Renderer/GraphicsContext.h"
#include "GLFW/glfw3.h"
namespace Pirates
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowhandle);
		virtual void Init()	override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;

	};
}