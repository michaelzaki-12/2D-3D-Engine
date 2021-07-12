#include "PEPCH.h"
#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGl/OpenGLShader.h"
#include "Renderer2D.h"
#include <memory>
namespace Pirates
{
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::Init()
	{
		PR_PROFILE_FUNCTION();

		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t Width, uint32_t Height)
	{
		RenderCommand::SetViewport(0, 0, Width, Height);
	}

	void Renderer::BeginScene(OrthoGraphicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexarray, const Ref<Shader>& shader, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMatrix", m_SceneData->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);
		vertexarray->Bind();
		RenderCommand::DrawIndexed(vertexarray);

	}
}