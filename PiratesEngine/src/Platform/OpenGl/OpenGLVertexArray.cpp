#include "PEPCH.h"
#include "OpenGLVertexArray.h"
#include <GLAD/glad.h>
namespace Pirates
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Pirates::ShaderDataType::None:
		case Pirates::ShaderDataType::Float: return GL_FLOAT;
		case Pirates::ShaderDataType::Float2:return GL_FLOAT;
		case Pirates::ShaderDataType::Float3:return GL_FLOAT;
		case Pirates::ShaderDataType::Float4:return GL_FLOAT;
		case Pirates::ShaderDataType::Mat3:return GL_FLOAT;
		case Pirates::ShaderDataType::Mat4:return GL_FLOAT;
		case Pirates::ShaderDataType::Int:return GL_INT;
		case Pirates::ShaderDataType::Int2:return GL_INT;
		case Pirates::ShaderDataType::Int3:return GL_INT;
		case Pirates::ShaderDataType::Int4:return GL_INT;
		case Pirates::ShaderDataType::Bool:return GL_BOOL;

		}
		PR_CORE_ASSERT(false, "UnKnown ShaderType");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		PR_PROFILE_FUNCTION();
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		PR_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		PR_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		PR_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer)
	{
		PR_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		vertexbuffer->Bind();
		uint32_t index = 0;
		const auto& layout = vertexbuffer->GetLayout();
		for (const auto& element : (BufferLayout)layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index,
				element.GetComponentsCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normolized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(UINT_PTR)element.OffSet);
			index++;
		}
		m_VertexBuffer.push_back(vertexbuffer);

	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer)
	{
		PR_PROFILE_FUNCTION();
		glBindVertexArray(m_RendererID);
		indexbuffer->Bind();

		m_IndexBuffer = indexbuffer;
	}

	void OpenGLVertexArray::SetLayout(const BufferLayout layout)
	{
	}

}