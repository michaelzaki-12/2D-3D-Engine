#include "PEPCH.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGl/OpenGLBuffer.h"

namespace Pirates
{

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:		 PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:		 return std::make_shared<OpenGLVertexBuffer>(size);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;

		return Ref<VertexBuffer>();
	}
	Ref<VertexBuffer> VertexBuffer::Create(float* Verticies, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
			case RendererAPI::API::None:		 PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::API::OpenGL:		 return std::make_shared<OpenGLVertexBuffer>(Verticies, size);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;

	}



	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* Indecies, uint32_t size)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None: PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(Indecies, size);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;
	}


}