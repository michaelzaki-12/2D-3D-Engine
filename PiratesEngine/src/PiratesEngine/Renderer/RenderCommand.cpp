#include "PEPCH.h"
#include "RenderCommand.h"
#include "Platform/OpenGl/OpenGLRendererAPI.h"

namespace Pirates
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;



}