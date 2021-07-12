#include "PEPCH.h"
#include "Texture.h"
#include "Renderer.h"
#include "PiratesEngine/Core/Core.h"
#include "RendererAPI.h"
#include "Platform/OpenGl/OpenGLTexture.h"
namespace Pirates
{
	Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:		PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:	 return std::make_shared<OpenGLTexture2D>(width, height);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;

	}
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:		PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:	 return std::make_shared<OpenGLTexture2D>(path);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;
		return Ref<Texture2D>();
	}

}