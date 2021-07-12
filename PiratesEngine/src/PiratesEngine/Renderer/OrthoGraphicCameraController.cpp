#include "PEPCH.h"
#include "OrthoGraphicCameraController.h"
#include "PiratesEngine/Core/Input.h"
#include <PiratesEngine/Core/KeyCode.h>

namespace Pirates
{
	OrthoGraphicCameraController::OrthoGraphicCameraController(float aspectRatio, bool Rotation)
		: m_AspectRatio(aspectRatio),  m_Bounds({ -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel }),m_Camera(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top), m_Rotation(Rotation)
	{

	}
	void OrthoGraphicCameraController::onUpdate(TimeStep ts)
	{
		PR_PROFILE_FUNCTION();

		if (Input::IsKeyPressed(PR_KEY_W))
		{
			m_CameraPosition.y -= m_Speed * ts;
		}
		else if (Input::IsKeyPressed(PR_KEY_S))
		{
			m_CameraPosition.y += m_Speed * ts;
		}
		if (Input::IsKeyPressed(PR_KEY_D))
		{
			m_CameraPosition.x -= m_Speed * ts;
		}
		else  if (Input::IsKeyPressed(PR_KEY_A))
		{
			m_CameraPosition.x += m_Speed * ts;
		}
		if (m_Rotation)
		{
			if (Input::IsKeyPressed(PR_KEY_LEFT))
			{
				m_Camera.Rotation -= 10.0f * ts;
			}
			if (Input::IsKeyPressed(PR_KEY_RIGHT))
			{
				m_Camera.Rotation += 10.0f * ts;
			}
			m_Camera.SetRotation(m_Camera.Rotation);
		}
		if (Input::IsKeyPressed(PR_KEY_I)) // Up
		{
			m_SquarePosition.y += m_SquareSpeed * ts;
		}
		if (Input::IsKeyPressed(PR_KEY_K)) // Down
		{
			m_SquarePosition.y -= m_SquareSpeed * ts;
		}
		if (Input::IsKeyPressed(PR_KEY_L)) // Right
		{
			m_SquarePosition.x += m_SquareSpeed * ts;
		}
		if (Input::IsKeyPressed(PR_KEY_J)) // Left
		{
			m_SquarePosition.x -= m_SquareSpeed * ts;
		}
		m_Camera.SetPosition(m_CameraPosition);
		m_Speed = m_ZoomLevel;
	}
	void OrthoGraphicCameraController::OnEvent(Event& e)
	{
		PR_PROFILE_FUNCTION();

		EventDispatcher dispathcher(e);
		dispathcher.DisPatch<MouseScrolledEvent>(PR_BIND_EVENT_FN(OrthoGraphicCameraController::OnMouseScrolled));
		dispathcher.DisPatch<WindowResizeEvent>(PR_BIND_EVENT_FN(OrthoGraphicCameraController::OnWindowResized));

	}
	bool OrthoGraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		PR_PROFILE_FUNCTION();

		m_ZoomLevel -= e.GetYOffSet();
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel , -m_ZoomLevel,m_ZoomLevel };
		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);

		return false;
	}
	bool OrthoGraphicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		PR_PROFILE_FUNCTION();


		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Bounds = { -m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel , -m_ZoomLevel,m_ZoomLevel };

		m_Camera.SetProjection(m_Bounds.Left, m_Bounds.Right, m_Bounds.Bottom, m_Bounds.Top);
		return false;
	}
}