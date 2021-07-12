#pragma once
#include "PiratesEngine/Renderer/RendererAPI.h"

namespace Pirates
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;

		virtual void Clear() override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t Width, uint32_t Height) override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexarray, uint32_t indexcount = 0) override;


	};

}