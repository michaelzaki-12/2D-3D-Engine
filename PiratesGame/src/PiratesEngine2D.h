#pragma once
#include "Pirates.h"
#include <vector>
#include "Particles.h"

class PiratesEngine2D : public Pirates::Layer
{
public:
	PiratesEngine2D();
	virtual ~PiratesEngine2D() = default;
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	void OnUpdate(Pirates::TimeStep ts) override;
	virtual void OnImGuiRender();
	void OnEvent(Pirates::Event& e) override;
private:
	Pirates::OrthoGraphicCameraController m_cameracontroller;
	// temproray
	Pirates::Ref<Pirates::Shader>m_Shader2;
	Pirates::Ref<Pirates::VertexBuffer> m_VertexBuffer;
	Pirates::Ref<Pirates::VertexArray> m_VertexArray, m_SquareVertexArray;
	Pirates::Ref<Pirates::IndexBuffer> m_IndexBuffer;
	Pirates::Ref<Pirates::Texture2D> m_PiratesLogoTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
	ParticleSystem m_Particles;
	ParticleProps m_ParticlesProps;
};
