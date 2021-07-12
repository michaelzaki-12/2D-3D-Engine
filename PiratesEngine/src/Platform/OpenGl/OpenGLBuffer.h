#pragma once
#include "PEPCH.h"
#include "PiratesEngine/Renderer/Buffer.h"

namespace Pirates
{


	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* Verticies, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);

		virtual void SetData(void* Data, uint32_t size) override;

		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual const BufferLayout& GetLayout() const override { return m_layout; }
		virtual void SetLayout(const BufferLayout layout) override { m_layout = layout; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_layout;
	};
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* Indecies, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const;
		virtual void UnBind() const;

		virtual uint32_t GetCount() const { return m_Count; }
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};

}
