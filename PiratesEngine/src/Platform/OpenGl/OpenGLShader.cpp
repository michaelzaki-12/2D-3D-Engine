#include "PEPCH.h"
#include "OpenGLShader.h"
#include "glm/glm.hpp"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <vector>

namespace Pirates
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "pixel" || type == "fragment") return GL_FRAGMENT_SHADER;
		PR_CORE_ASSERT(false, "UnKnown Shader Type!")
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath)
	{
		PR_PROFILE_FUNCTION();

		std::string ShaderSource = 	ReadFile(filepath);
		auto shadersources = PreProcess(ShaderSource);
		Compile(shadersources);
		// asssets/shader/texture.glsl
		auto lastslash = filepath.find_last_of("/\\");
		lastslash = lastslash == std::string::npos ? 0 : lastslash +1;
		auto lastdot = filepath.rfind(".");
		auto count = lastdot == std::string::npos ? filepath.size() - lastslash : lastdot - lastslash;

		m_Name = filepath.substr(lastslash, count);

	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& Vertexsrc, const std::string& Fragmentsrc) : m_Name(name)
	{
		PR_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER] = Vertexsrc;
		sources[GL_FRAGMENT_SHADER] = Fragmentsrc;
		Compile(sources);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath)
	{
		PR_PROFILE_FUNCTION();

		std::string result;
		std::ifstream in(filepath, std::ios::in , std::ios::binary);
		if (in)
		{
			in.seekg(1, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[4], result.size());

			in.close();
		}
		else
		{
			PR_CORE_ERROR("could not open file '{0}'", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		PR_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> ShaderResources;

		const char* typetoken = "#type";
		size_t typeTokenLength = strlen(typetoken);
		size_t pos = source.find(typetoken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			PR_CORE_ASSERT(eol != std::string::npos, "Synax Error");
			size_t begin = pos + typeTokenLength + 1;
			std::string  type = source.substr(begin, eol - begin);
			PR_CORE_ASSERT(ShaderTypeFromString(type), "Invaild Shader Type");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typetoken, nextLinePos);
			ShaderResources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
				pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}
		return ShaderResources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& ShaderSources)
	{
		PR_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		PR_CORE_ASSERT(ShaderSources.size() <= 2, "We only Support 2 Shaders");
		std::array<GLenum, 2> glshaderIDs{};
		int glShaderIDsindex = 0;
		for (auto& kv : ShaderSources)
		{
			GLenum Shadertype = kv.first;
			const std::string& source = kv.second;
			GLuint Shader = glCreateShader(Shadertype);

			// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
			const GLchar* sourceCTR = source.c_str();
			glShaderSource(Shader, 1, &sourceCTR, 0);

			// Compile the vertex shader
			glCompileShader(Shader);

			GLint isCompiled = 0;
			glGetShaderiv(Shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(Shader, maxLength, &maxLength, &infoLog[0]);

				// We don't need the shader anymore.
				glDeleteShader(Shader);

				PR_CORE_ASSERT(false, "Shader Compiling Falied");
				PR_CORE_ERROR("{0}", infoLog.data());

				// Use the infoLog as you see fit.

				// In this simple program, we'll just leave
				break;
			}
			glAttachShader(program, Shader);
			glshaderIDs[glShaderIDsindex++] = Shader;
		}
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			for (auto id : glshaderIDs)
				glDeleteShader(id);
			// Use the infoLog as you see fit.
			PR_CORE_ERROR("Shader Link Falied");
			PR_CORE_ERROR("{0}", infoLog.data());

			// In this simple program, we'll just leave

			return;
		}
		// Always detach shaders after a successful link.
		for (auto id : glshaderIDs)
			glDetachShader(program, id);

		m_RendererID = program;
	}


	void OpenGLShader::Bind() const
	{
		PR_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}
	void OpenGLShader::UnBind() const
	{
	}
	void Shader::UnBind() const
	{
		glUseProgram(0);
	}


	void OpenGLShader::UploadUniformFloat4(const std::string name, const glm::vec4& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.a);
	}

	void OpenGLShader::UploadUniformIntArray(const std::string name, int* values, uint32_t counts)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1iv(location, counts, values);
	}

	void OpenGLShader::UploadUniformInt(const std::string name, int values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, values);
	}

	void OpenGLShader::UploadUniformMat3(const std::string name, const glm::mat3& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}


	void OpenGLShader::UploadUniformFloat(const std::string name, const float values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, (GLint)values);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string name, const glm::vec2& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string name, const glm::vec3& values)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}
	void OpenGLShader::UploadUniformMat4(const std::string name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));

	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		PR_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}
	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		PR_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}
	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		PR_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}
	void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t counts)
	{
		UploadUniformIntArray(name, values, counts);
	}
	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		PR_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

}