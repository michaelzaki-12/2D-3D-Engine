#pragma once
#include "PiratesEngine/Renderer/OrthoGraphicCamera.h"
#include "PiratesEngine/Core/TimeStep.h"
#include "PiratesEngine/Events/MouseEvent.h"
#include "PiratesEngine/Events/ApplicationEvent.h"

namespace Pirates
{
	struct OrthographicCameraBounds
	{
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};
	class OrthoGraphicCameraController
	{
	public:
		OrthoGraphicCameraController(float aspectRatio, bool Rotation = false);
	
		void onUpdate(TimeStep ts);
		void OnEvent(Event& e);
	
		OrthoGraphicCamera& GetCamera() { return m_Camera; }
		const OrthoGraphicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel()const { return m_ZoomLevel; }
		void SetZoomLevel(float level) { m_ZoomLevel = level; }

		const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float m_Speed = 1.0f;
		glm::vec3 m_SquarePosition;
		float m_SquareSpeed = 1.0f;
		glm::vec3 m_CameraPosition = {0.0, 0.0, 0.0};
		bool m_Rotation;
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCameraBounds m_Bounds;
		OrthoGraphicCamera m_Camera;

	};

}