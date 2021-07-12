#pragma once

#include "glm/glm.hpp"
namespace Pirates
{

	class OrthoGraphicCamera 
	{
	public:
		OrthoGraphicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);


		void SetPosition(const glm::vec3& position) { m_Position = position; ReCalculateViewMatrix(); }
		void SetRotation(float rotation) { m_Rotation = rotation; ReCalculateViewMatrix(); }
		
		const glm::vec3& GetPosition() const { return m_Position; }
		float GetRotation() const { return m_Rotation; }
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		static bool IsKeyPressedImpl(int keycode);

		float x = 0.0f;
		float y = 0.0f;
		float z = 1.0f;
		float Rotation = 0.0f;
	private:
		void ReCalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position;

		float m_Rotation = 0.0f; // Untill Now ///// 
	};
}