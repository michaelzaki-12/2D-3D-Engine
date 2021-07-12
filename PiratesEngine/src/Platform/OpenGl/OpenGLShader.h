#pragma once
#include "glm/glm.hpp"
#include "PiratesEngine/Renderer/Shader.h"
typedef unsigned int GLenum;
namespace Pirates
{
	class OpenGLShader : public Shader
	{
	public:		
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name,const std::string& Vertexsrc, const std::string& Fragmentsrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const std::string& GetName() const override { return m_Name; }

		void UploadUniformMat3(const std::string name, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string name, const glm::mat4& matrix);

		void UploadUniformFloat(const std::string name, const float values);
		void UploadUniformFloat2(const std::string name, const glm::vec2& values);
		void UploadUniformFloat3(const std::string name, const glm::vec3& values);
		void UploadUniformFloat4(const std::string name, const glm::vec4& values);
	
		virtual void SetIntArray(const std::string& name, int* values, uint32_t counts) override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat3(const std::string& name,const glm::vec3& value) override;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;

		void UploadUniformIntArray(const std::string name, int* values, uint32_t counts);
		void UploadUniformInt(const std::string name, int values);
	private:
		std::string ReadFile(const std::string& filepath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& ShaderSources);
	private:
		uint32_t m_RendererID;
		std::string m_Name;
	};


}