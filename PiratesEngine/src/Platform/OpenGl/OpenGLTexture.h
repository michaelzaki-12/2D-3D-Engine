#pragma once
#include "PiratesEngine/Renderer/Texture.h"
#include <string>

namespace Pirates
{
	
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		virtual ~OpenGLTexture2D();
		
		virtual bool operator==(const Texture& Other) const override 
		{
			return m_RendererID == ((OpenGLTexture2D&)Other).m_RendererID;
		}

		virtual uint32_t GetWight() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual void Bind(uint32_t slot = 0) const override;

		virtual void SetData(void* data, uint32_t size) override;

	private:
		std::string m_Path;

		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		unsigned int  m_InternalFormat, m_DataFormat;
	};

}