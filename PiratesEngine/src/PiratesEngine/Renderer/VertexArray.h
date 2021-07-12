#pragma once
#include "PiratesEngine/Renderer/Buffer.h"
#include <memory>

namespace Pirates
{
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexbuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& Indexbuffer) = 0;
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffer() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;
		
		virtual void SetLayout(const BufferLayout layout) = 0;

		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;

		static Ref<VertexArray> Create();

	};


}