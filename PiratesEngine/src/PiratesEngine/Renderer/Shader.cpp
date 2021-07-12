#include "PEPCH.h"
#include "PiratesEngine/Renderer/Shader.h"
#include "Renderer.h"
#include "Platform/OpenGl/OpenGLVertexArray.h"
#include "Platform/OpenGl/OpenGLShader.h"

namespace Pirates
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:	PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
		case RendererAPI::API::OpenGL:	 return std::make_shared<OpenGLShader>(filepath);
		}

		PR_CORE_ASSERT(false, "UnKnown RendererAPI");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name,const std::string& Vertexsrc, const std::string& Fragmentsrc)
	{
		switch (Renderer::GetApi())
		{
			case RendererAPI::API::None:	 PR_CORE_ASSERT(false, "RendererAPI::None is currently not supported") return nullptr;
			case RendererAPI::API::OpenGL:	 return std::make_shared<OpenGLShader>(name, Vertexsrc, Fragmentsrc);
		}

	PR_CORE_ASSERT(false, "UnKnown RendererAPI");
	return nullptr;
	}

	void shaderlibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		PR_CORE_ASSERT(!Exisits(name), "Shader Already exist");
		m_Shaders[name] = shader;
	}

	void shaderlibrary::Add(const Ref<Shader>& shader)
	{
		auto& name= shader->GetName();
		Add(name, shader);
	}

	Ref<Shader> shaderlibrary::Load1(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
		return Ref<Shader>();
	}

	Ref<Shader> shaderlibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
		return Ref<Shader>();
	}

	Ref<Shader> shaderlibrary::Get(const std::string& name)
	{
		PR_CORE_ASSERT(Exisits(name), "Shader Not Found");
		return m_Shaders[name];
		return Ref<Shader>();
	}

	bool shaderlibrary::Exisits(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
