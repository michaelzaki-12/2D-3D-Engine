#include "PEPCH.h"
#include "Renderer2D.h"
#include "glm/gtc/matrix_transform.hpp"
#include "RenderCommand.h"

namespace Pirates
{
	struct QuadVertex
	{
		glm::vec3 position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TillingFactor = 1.0f;
		//TODO: Have A  texid, may be Something else;

	};
	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 100000;
		static const uint32_t MaxVerticies = MaxQuads * 4;
		static const uint32_t MaxIndecies= MaxQuads * 6;
		static const uint32_t MaxTextureSlot = 32;

		uint32_t IndexCount = 0;

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> Whitetexture;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferptr= nullptr;
		
		std::array< Ref<Texture2D>, MaxTextureSlot> TextureSlots;
		uint32_t TextureSlotsIndex = 1;

		glm::vec4 QuadVertexPosition[4];

		Renderer2D::Statistics Stats;
	};
	static  Renderer2DData s_Data;


	void Renderer2D::Init()
	{
		PR_PROFILE_FUNCTION();

		s_Data.QuadVertexArray = VertexArray::Create();

		s_Data.QuadVertexBuffer =   VertexBuffer::Create(s_Data.MaxVerticies * sizeof(QuadVertex));
		s_Data.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TillingFactor" },
		});

		s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

		s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVerticies];

		uint32_t* QuadIndcies = new uint32_t[s_Data.MaxIndecies];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndecies; i += 6)
		{
			QuadIndcies[i + 0] = offset + 0;
			QuadIndcies[i + 1] = offset + 1;
			QuadIndcies[i + 2] = offset + 2;

			QuadIndcies[i + 3] = offset + 2;
			QuadIndcies[i + 4] = offset + 3;
			QuadIndcies[i + 5] = offset + 0;
			offset += 4;
		}

		Ref<IndexBuffer> squareIB = IndexBuffer::Create(QuadIndcies, s_Data.MaxIndecies);
		s_Data.QuadVertexArray->SetIndexBuffer(squareIB);

		delete[] QuadIndcies;

		s_Data.Whitetexture = Texture2D::Create(1, 1);
		uint32_t WhiteTextureData = 0xffffffff;
		s_Data.Whitetexture->SetData(&WhiteTextureData, sizeof(WhiteTextureData));

		uint32_t samplers[s_Data.MaxTextureSlot];
		for (int i = 0; i < s_Data.MaxTextureSlot; i++)
		{
			samplers[i] = i;
		}

		s_Data.TextureShader = Shader::Create("Shaders/texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetIntArray("u_Texture", (int*)samplers ,s_Data.MaxTextureSlot);

		//set all texture slots to zero
		s_Data.TextureSlots[0] = s_Data.Whitetexture;
	    
		s_Data.QuadVertexPosition[0] = { -0.5f,-0.5f,0.0f,1.0f };
		s_Data.QuadVertexPosition[1] = { 0.5f,-0.5f,0.0f,1.0f };
		s_Data.QuadVertexPosition[2] = { 0.5f,0.5f,0.0f,1.0f };
		s_Data.QuadVertexPosition[3] = { -0.5f,0.5f,0.0f,1.0f };
	}
	void Renderer2D::ShutDown()
	{
		PR_PROFILE_FUNCTION();

	}

	void Renderer2D::BeginScene(const OrthoGraphicCamera& m_Camera)
	{
		PR_PROFILE_FUNCTION();

		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjectionMatrix", m_Camera.GetViewProjectionMatrix());
		
		s_Data.IndexCount = 0;
		s_Data.QuadVertexBufferptr = s_Data.QuadVertexBufferBase;
		s_Data.TextureSlotsIndex = 1;
	}
	void Renderer2D::EndScene()
	{
		PR_PROFILE_FUNCTION();

		uint32_t datasize = (uint8_t*)s_Data.QuadVertexBufferptr - (uint8_t*)s_Data.QuadVertexBufferBase;
		s_Data.QuadVertexBuffer->SetData(s_Data.QuadVertexBufferBase, datasize);

		Flush();
	}
	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.TextureSlotsIndex;i++)
		{
			s_Data.TextureSlots[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.IndexCount);

		s_Data.Stats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_Data.IndexCount = 0;
		s_Data.QuadVertexBufferptr = s_Data.QuadVertexBufferBase;

		s_Data.TextureSlotsIndex = 1;
	}
	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const glm::vec4& color, const float TillingFactor)
	{
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, color, TillingFactor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const glm::vec4& color, const float TillingFactor)
	{
		PR_PROFILE_FUNCTION();
		constexpr float  whitetexture = 0.0f;

		if (s_Data.IndexCount >= Renderer2DData::MaxIndecies)
			FlushAndReset();
		

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });

		s_Data.QuadVertexBufferptr->position =  transform * s_Data.QuadVertexPosition[0];
		s_Data.QuadVertexBufferptr->Color =  color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = whitetexture;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[1];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = whitetexture;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[2];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = whitetexture;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[3];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = whitetexture;
		s_Data.QuadVertexBufferptr++;

		s_Data.IndexCount += 6;
		s_Data.Stats.QuadCount++;

	}

	void Renderer2D::DrawQuad(const glm::vec2& Position, const glm::vec2& Size, const Ref<Texture2D>& texture, const float TillingFactor)
	{
		DrawQuad({ Position.x, Position.y, 0.0f }, Size, texture, TillingFactor);
	}
	void Renderer2D::DrawQuad(const glm::vec3& Position, const glm::vec2& Size, const Ref<Texture2D>& texture, const float TillingFactor)
	{
		PR_PROFILE_FUNCTION();
		if (s_Data.IndexCount >= Renderer2DData::MaxIndecies)
			FlushAndReset();

		constexpr glm::vec4 color = { 1.0f,1.0f ,1.0f ,1.0f };

		float textureindex = 0;
		for (uint32_t i = 1; i < s_Data.TextureSlotsIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get()) 
			{
				textureindex = (float)i;
				break;
			}
		}

		if (textureindex == 0.0f)
		{
			textureindex = (float)s_Data.TextureSlotsIndex;
			s_Data.TextureSlots[s_Data.TextureSlotsIndex] = texture;
			s_Data.TextureSlotsIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[0];
		
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[1];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[2];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[3];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.IndexCount += 6;
		s_Data.Stats.QuadCount++;


	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, const glm::vec2& Size, float Rotation, const glm::vec4& color, const float TillingFactor)
	{
		DrawRotatedQuad({ Position.x, Position.y, 0.0f }, Size, Rotation, color, TillingFactor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, const glm::vec2& Size, float Rotation, const glm::vec4& color, const float TillingFactor)
	{
		if (s_Data.IndexCount >= Renderer2DData::MaxIndecies)
			FlushAndReset();

		float textureindex = 0;

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::rotate(glm::mat4(1.0f),  Rotation,{ 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[0];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[1];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[2];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[3];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.IndexCount += 6;

		s_Data.Stats.QuadCount++;

	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& Position, const glm::vec2& Size, float Rotation, const Ref<Texture2D>& texture, const float TillingFactor)
	{
		DrawRotatedQuad({ Position.x, Position.y, 0.0f}, Size, Rotation, texture, TillingFactor);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3& Position, const glm::vec2& Size, float Rotation, const Ref<Texture2D>& texture, const float TillingFactor)
	{
		PR_PROFILE_FUNCTION();

		if (s_Data.IndexCount >= Renderer2DData::MaxIndecies)
			FlushAndReset();

		constexpr glm::vec4 color = { 1.0f,1.0f ,1.0f ,1.0f };

		float textureindex = 0;
		for (uint32_t i = 1; i < s_Data.TextureSlotsIndex; i++)
		{
			if (*s_Data.TextureSlots[i].get() == *texture.get())
			{
				textureindex = (float)i;
				break;
			}
		}

		if (textureindex == 0.0f)
		{
			textureindex = (float)s_Data.TextureSlotsIndex;
			s_Data.TextureSlots[s_Data.TextureSlotsIndex] = texture;
			s_Data.TextureSlotsIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), Position) *
			glm::rotate(glm::mat4(1.0f), Rotation, { 0.0f, 0.0f, 1.0f }) *
			glm::scale(glm::mat4(1.0f), { Size.x, Size.y, 1.0f });

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[0];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[1];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 0.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[2];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 1.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.QuadVertexBufferptr->position = transform * s_Data.QuadVertexPosition[3];
		s_Data.QuadVertexBufferptr->Color = color;
		s_Data.QuadVertexBufferptr->TexCoord = { 0.0f, 1.0f };
		s_Data.QuadVertexBufferptr->TexIndex = textureindex;
		s_Data.QuadVertexBufferptr->TillingFactor = TillingFactor;
		s_Data.QuadVertexBufferptr++;

		s_Data.IndexCount += 6;

		s_Data.Stats.QuadCount++;
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{

		return s_Data.Stats;
	}

	void Renderer2D::ResetStats()
	{
		memset(&s_Data.Stats, 0, sizeof(Statistics));

	}
	
}