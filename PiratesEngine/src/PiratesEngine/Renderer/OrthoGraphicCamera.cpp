#include "PEPCH.h"
#include "PiratesEngine/Core/Application.h"
#include "OrthoGraphicCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include <GLFW/glfw3.h>

namespace Pirates
{
	OrthoGraphicCamera::OrthoGraphicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		PR_PROFILE_FUNCTION();

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void OrthoGraphicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		PR_PROFILE_FUNCTION();

		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	bool OrthoGraphicCamera::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return  state == GLFW_PRESS || state == GLFW_REPEAT;
	}


	void OrthoGraphicCamera::ReCalculateViewMatrix()
	{
		PR_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}
}