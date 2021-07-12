#include "PEPCH.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Pirates
{
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_Width(width), m_Height(height)
	{
		PR_PROFILE_FUNCTION();
		m_InternalFormat = GL_RGBA, m_DataFormat = GL_RGB;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_Path(path)
	{
		PR_PROFILE_FUNCTION();
		stbi_set_flip_vertically_on_load(1);
		int width, height, channels;
		stbi_uc* data = nullptr;
		{
			PR_PROFILE_SCOPE("stbiload Function (loading textures)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 4);
		}
		m_Width = width;
		m_Height = height;

		PR_CORE_ASSERT(data, "Failes To Load Image!");
		GLenum internalformat = 0, dataformat = 0;
		if (channels == 1)
		{
			internalformat = GL_RGBA;
			dataformat = GL_RGBA;
		}
		else if (channels == 4)
		{
			internalformat = GL_RGBA8;
			dataformat = GL_RGBA;
		}
		m_InternalFormat = internalformat;
		m_DataFormat= dataformat;

		PR_CORE_ASSERT(internalformat & dataformat, "Format dont Supportted");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalformat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataformat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}



	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		PR_PROFILE_FUNCTION();
		//glActiveTexture(GL_TEXTURE0 + slot);

		glBindTextureUnit(slot, m_RendererID);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		PR_PROFILE_FUNCTION();
		uint32_t bpc = m_DataFormat == GL_RGBA ? 4 : 3;
		PR_CORE_ASSERT(size == m_Width * m_Height * bpc, "Data Must be Entire Texture");
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		PR_PROFILE_FUNCTION();
		glDeleteTextures(1, &m_RendererID);
	}

}