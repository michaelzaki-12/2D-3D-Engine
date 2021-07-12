#include <Pirates.h>
#include "PiratesEngine/Core/EntryPoint.h"
#include "imgui.h"
#include <vector>
#include "PiratesEngine2D.h"
class ExampleLayer : public Pirates::Layer
{
public:
	ExampleLayer() : Layer("Example"),m_cameracontroller(1280.0f/720.0f)
	{
		m_VertexArray = Pirates::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
		};
		m_VertexBuffer = Pirates::VertexBuffer::Create(vertices, sizeof(vertices));
		Pirates::BufferLayout layout = {
			{ Pirates::ShaderDataType::Float3, "a_Position" },
			{ Pirates::ShaderDataType::Float4, "a_Color" }
		};
		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		
		uint32_t indices[3] = { 0, 1, 2 };
		m_IndexBuffer = Pirates::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_SquareVertexArray =  Pirates::VertexArray::Create();
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
		};
		Pirates::Ref<Pirates::VertexBuffer> squareVB;
		squareVB = Pirates::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		Pirates::BufferLayout Squarelayout = {
			{ Pirates::ShaderDataType::Float3, "a_Position" },
			{ Pirates::ShaderDataType::Float2, "a_TexCoord" },
		};

		squareVB->SetLayout(Squarelayout);
		m_SquareVertexArray->AddVertexBuffer(squareVB);
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Pirates::Ref<Pirates::IndexBuffer> squareIB;
		squareIB = Pirates::IndexBuffer::Create(squareIndices, 3 *  sizeof(squareIndices) / sizeof(uint32_t));
		m_SquareVertexArray->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform *  vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_Shader = Pirates::Shader::Create("VertexColorPos",vertexSrc, fragmentSrc);

		std::string ShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			uniform mat4 u_ViewProjectionMatrix;
			uniform mat4 u_Transform;
			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjectionMatrix * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string ShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";
		m_Shader2 = Pirates::Shader::Create("SquareVertexPos", ShaderVertexSrc, ShaderFragmentSrc);

		//m_TextureShader = Pirates::Shader::Create("Shaders/texture.glsl");

		auto textureshader = m_shaderlibrary.Load1("Shaders/texture.glsl");

		m_Texture = Pirates::Texture2D::Create("PiratesLogo/Pirates.png");
		LogoTexture = Pirates::Texture2D::Create("PiratesLogo/Logo.png");

		std::dynamic_pointer_cast<Pirates::OpenGLShader>(textureshader)->Bind();
		std::dynamic_pointer_cast<Pirates::OpenGLShader>(textureshader)->UploadUniformInt("u_Texture", 0);
}
	void OnUpdate(Pirates::TimeStep ts) override
	{
		m_cameracontroller.onUpdate(ts);

		bool DarkMode = true;
		if (DarkMode == true)
			Pirates::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		else
			Pirates::RenderCommand::SetClearColor({ 1.0f, 1.0f, 1.0f, 1.0f });
		Pirates::RenderCommand::Clear();

		Pirates::Renderer::BeginScene(m_cameracontroller.GetCamera());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));


		std::dynamic_pointer_cast<Pirates::OpenGLShader>(m_Shader2)->Bind();
		std::dynamic_pointer_cast<Pirates::OpenGLShader>(m_Shader2)->UploadUniformFloat3("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos{ x * 0.11f, y * 0.11f, 0.0f };
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Pirates::Renderer::Submit(m_SquareVertexArray, m_Shader2, transform);
			}			
		}
		auto textureshader = m_shaderlibrary.Get("texture");

		m_Texture->Bind();
		Pirates::Renderer::Submit(m_SquareVertexArray, textureshader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		LogoTexture->Bind();
		Pirates::Renderer::Submit(m_SquareVertexArray, textureshader,
			glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.63f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		//triangle
		//Pirates::Renderer::Submit(m_VertexArray, m_Shader);
	}
private:
	Pirates::shaderlibrary m_shaderlibrary;
	Pirates::Ref<Pirates::Shader> m_Shader;
	Pirates::Ref<Pirates::VertexBuffer> m_VertexBuffer;
	Pirates::Ref<Pirates::IndexBuffer> m_IndexBuffer;
	Pirates::Ref<Pirates::VertexArray> m_VertexArray;
	
	Pirates::Ref<Pirates::Texture2D> m_Texture, LogoTexture;
	Pirates::Ref<Pirates::Shader> m_Shader2;
	Pirates::Ref<Pirates::VertexArray> m_SquareVertexArray;
	Pirates::OrthoGraphicCameraController m_cameracontroller;

	glm::vec3 m_SquareColor = {0.2f, 0.3f, 0.8f};

public:
	virtual void OnImGuiRender()
	{
		ImGui::Begin("settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));

		ImGui::End();
	}

	void OnEvent(Pirates::Event& e) override
	{
		m_cameracontroller.OnEvent(e);
	}
};

class PiratesGame : public Pirates::Application {
public:
	PiratesGame() 
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new PiratesEngine2D());
		PushOverlay(new Pirates::ImGuiLayer());
	}
	~PiratesGame() 
	{
	}
};
Pirates::Application*  Pirates::CreateApplication()
{
	return new PiratesGame();
}