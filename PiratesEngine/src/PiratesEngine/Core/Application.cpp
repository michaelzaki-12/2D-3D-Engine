#include "PEPCH.h"
#include "Application.h"
#include "PiratesEngine/ImGui/ImGuiLayer.h"
#include "Imgui.h"
#include "PiratesEngine/Renderer/Renderer.h"
#include "PiratesEngine/Events/ApplicationEvent.h"
#include "Input.h"
#include "PiratesEngine/Renderer/Renderer.h"
#include "PiratesEngine/Renderer/Renderer2D.h"
#include "PiratesEngine/Renderer/RenderCommand.h"
#include "GLFW/glfw3.h"
namespace Pirates 
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PR_PROFILE_FUNCTION();

		PR_CORE_ASSERT(!s_Instance, "Applciation iS FUCKING NOT WORKING");
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = std::make_unique<ImGuiLayer>();
		Renderer::Init();
	}

	void Application::PushLayer(Layer* layer)
	{
		PR_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		PR_PROFILE_FUNCTION();

		m_LayerStack.PushOverLay(layer);
		layer->OnAttach();
	}


	void Application::OnEvent(Event& e)
	{
		PR_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.DisPatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.DisPatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.m_Handled)
				break;
			(*--it)->OnEvent(e);
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		PR_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

	void Application::Run()
	{
		PR_PROFILE_FUNCTION();

		while (m_Running)
		{
			float time = (float)glfwGetTime();
			TimeStep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			if (!m_Minimized)
			{
				{
					PR_PROFILE_SCOPE(" Layer On Update");
					for (Layer* layer : m_LayerStack)
					{
						layer->OnUpdate(timestep);
					}
				}
				auto [Xpos, Ypos] = Input::GetMousePosition();
			m_ImGuiLayer->Begin();
			{
				PR_PROFILE_SCOPE("layer OnImGuiRender");
				for (Layer* layer : m_LayerStack)
				{
					layer->OnImGuiRender();
				}
			}
			m_ImGuiLayer->End();
			}
			
			m_Window->OnUpdate();
		}
	}
	Application::~Application() 
	{
		PR_PROFILE_FUNCTION();
	}
}