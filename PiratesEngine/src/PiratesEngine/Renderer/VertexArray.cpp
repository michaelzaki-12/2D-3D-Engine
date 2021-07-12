#include "PEPCH.h"
#include "VertexArray.h"
#include "Platform/OpenGl/OpenGLBuffer.h"
//#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGLVertexArray.h"


namespace Pirates
{

	Ref<VertexArray> VertexArray::Create()
	{

		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:		 PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:	 return std::make_shared<OpenGLVertexArray>();
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;
	}



}