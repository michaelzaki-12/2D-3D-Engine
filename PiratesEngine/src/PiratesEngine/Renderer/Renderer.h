#pragma once
#include "RenderCommand.h"
#include <memory>
#include "OrthoGraphicCamera.h"
#include "Shader.h"
namespace Pirates
{

	class Renderer
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t Width, uint32_t Height);

		static void BeginScene(OrthoGraphicCamera& camera);
		static void EndScene();
		static void Submit(const Ref<VertexArray>& vertexarray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RendererAPI::API GetApi() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};
		static SceneData* m_SceneData;
	};
	
}