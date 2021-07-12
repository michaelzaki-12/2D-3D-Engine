#pragma once

#include "PiratesEngine/Renderer/VertexArray.h"

namespace Pirates
{

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexbuffer) override;

		virtual void SetLayout(const BufferLayout layout) override;


		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const { return m_VertexBuffer; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }


		virtual void Bind()const override;
		virtual void UnBind()const override;

	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffer;
		Ref<IndexBuffer> m_IndexBuffer;

	};



}