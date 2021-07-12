#pragma once
#include "RendererAPI.h"


namespace Pirates
{
	class RenderCommand
	{
	public:
		inline static void Init()
		{
			s_RendererAPI->Init();
		}
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}
		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height)
		{
			s_RendererAPI->SetViewport(x, y, Width, Height);
		}

		inline static void DrawIndexed(const Ref<VertexArray>& vertexarray, uint32_t count = 0)
		{
			s_RendererAPI->DrawIndexed(vertexarray, count);
		}
	private:
		static RendererAPI* s_RendererAPI;


	};

}