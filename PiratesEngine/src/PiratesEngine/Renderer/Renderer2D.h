#pragma once
#include "OrthoGraphicCamera.h"
#include "glm/glm.hpp"
#include "Shader.h"
#include "VertexArray.h"
#include "Texture.h"

namespace Pirates
{
	class Renderer2D
	{
	public:
		static void Init();
		static void ShutDown();

		static void Flush();

		static void BeginScene(const OrthoGraphicCamera& m_Camera);
		static void EndScene();
		// premartives
		static void DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& color,const float TillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& color,const float TillingFactor = 1.0f);

		static void DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const Ref<Texture2D>& texture, const float TillingFactor = 1.0f);
		static void DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const Ref<Texture2D>& texture, const float TillingFactor = 1.0f);

		static void DrawRotatedQuad(const glm::vec3& Position, const glm::vec2& Size,float Rotation, const glm::vec4& color,const float TillingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec2& Position, const glm::vec2& Size,float Rotation, const glm::vec4& color,const float TillingFactor = 1.0f);

		static void DrawRotatedQuad(const glm::vec2& Position, const glm::vec2& Size,float Rotation, const Ref<Texture2D>& texture,const float TillingFactor = 1.0f);
		static void DrawRotatedQuad(const glm::vec3& Position, const glm::vec2& Size, float Rotation, const Ref<Texture2D>& texture,const float TillingFactor = 1.0f);

		//Stats Struct
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t GetTotalVertciesCounts() { return QuadCount * 4; }
			uint32_t GetTotalIndexCounts() { return QuadCount * 6; }
		};

		static Statistics GetStats();
		static void ResetStats();
	private:
		static void FlushAndReset();

	};

}