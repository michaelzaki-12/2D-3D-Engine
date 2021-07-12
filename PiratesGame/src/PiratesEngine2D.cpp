#include "PiratesEngine2D.h"
#include <chrono>

PiratesEngine2D::PiratesEngine2D() : Layer("PiratesEngine2D"), m_cameracontroller(1280.0f / 720.0f)
{

}
void PiratesEngine2D::OnAttach()
{
	PR_PROFILE_FUNCTION();

	m_PiratesLogoTexture = Pirates::Texture2D::Create("PiratesLogo/Pirates.png");


	m_ParticlesProps.ColorBegin = { 254 / 255.0f, 212 / 255.0f, 123 / 255.0f, 1.0f };
	m_ParticlesProps.ColorEnd = { 254 / 255.0f, 109 / 255.0f, 41 / 255.0f, 1.0f };
	m_ParticlesProps.SizeBegin = 0.5f, m_ParticlesProps.SizeVariation = 0.3f, m_ParticlesProps.SizeEnd = 0.0f;
	m_ParticlesProps.LifeTime = 1.0f;
	m_ParticlesProps.Velocity = { 0.0f, 0.0f };
	m_ParticlesProps.VelocityVariation = { 3.0f, 1.0f };
	m_ParticlesProps.Position = { 0.0f, 0.0f };

}
void PiratesEngine2D::OnDetach()
{
	PR_PROFILE_FUNCTION();
}

void PiratesEngine2D::OnUpdate(Pirates::TimeStep ts)
{
	PR_PROFILE_FUNCTION();

	m_cameracontroller.onUpdate(ts);
	Pirates::Renderer2D::ResetStats();

	{
		bool DarkMode = true;
		if (DarkMode == true)
			Pirates::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		else
			Pirates::RenderCommand::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Pirates::RenderCommand::Clear();
	}
	static float Rotation = 0.0f;
	Rotation += ts * 20.0f;
	{
		Pirates::Renderer2D::BeginScene(m_cameracontroller.GetCamera());

		Pirates::Renderer2D::DrawQuad({ -1.0f ,0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Pirates::Renderer2D::DrawQuad({ 0.5f ,-0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Pirates::Renderer2D::DrawQuad({ -2.0f ,2.0f, -0.1f }, { 5.0f, 5.0f }, m_PiratesLogoTexture, 1.0f);
		//Pirates::Renderer2D::DrawRotatedQuad({ -5.0f ,5.0f, -0.1f }, { 5.0f, 5.0f }, Rotation, m_PiratesLogoTexture, 5.0f);
	    Pirates::Renderer2D::EndScene();
	}
	//triangle
	//Pirates::Renderer::Submit(m_VertexArray, m_Shader);

	if (Pirates::Input::IsMouseButtonPressed(PR_MOUSE_BUTTON_LEFT))
	{
		auto [x, y] = Pirates::Input::GetMousePosition();
		auto width  = Pirates::Application::Get().GetWindow().GetWidth();
		auto height = Pirates::Application::Get().GetWindow().GetHeight();

		auto bounds = m_cameracontroller.GetBounds();
		auto pos = m_cameracontroller.GetCamera().GetPosition();
		x = (x / width) * bounds.GetWidth() - bounds.GetWidth() * 0.5f;
		y = bounds.GetHeight() * 0.5f - (y / height) * bounds.GetHeight();
		m_ParticlesProps.Position = { x + pos.x, y + pos.y };
		for (int i = 0; i < 5; i++)
			m_Particles.Emit(m_ParticlesProps);
	}

	m_Particles.OnRender(m_cameracontroller.GetCamera());
	m_Particles.OnUpdate(ts);
	
	//TODO: Shader::setmat4 , shader::setfloat4 ADD These Functions
}
void PiratesEngine2D::OnImGuiRender()
{
	ImGui::Begin("settings");
	auto stats = Pirates::Renderer2D::GetStats();
	ImGui::Text("Renderer 2D Stats: ");
	ImGui::Text("Draw Calls:  %d", stats.DrawCalls);
	ImGui::Text("Quad:  %d", stats.QuadCount);
	ImGui::Text("Vertcies:  %d", stats.GetTotalVertciesCounts());
	ImGui::Text("Indecies:  %d", stats.GetTotalIndexCounts());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}
void PiratesEngine2D::OnEvent(Pirates::Event& e)
{
	m_cameracontroller.OnEvent(e);

}