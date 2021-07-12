#include "PEPCH.h"
#include "PiratesEngine/Core/Application.h"
#include <GLFW/glfw3.h>

#include "WindowsInput.h"

namespace Pirates
{


	 Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		
		return  state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool WindowsInput::IsMouseButtonPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, keycode);

		return state == GLFW_PRESS;
	}
	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double Xpos, Ypos;
		glfwGetCursorPos(window, &Xpos, &Ypos);
		return { (float)Ypos, (float)Xpos };

	}
	float WindowsInput::GetMouseXImpl()
	{
		auto [Xpos, Ypos] = GetMousePosImpl();
		return (float)Xpos;

	}
	float WindowsInput::GetMouseYImpl()
	{
		auto [Xpos, Ypos] = GetMousePosImpl();
		return (float)Ypos;

	}

}
