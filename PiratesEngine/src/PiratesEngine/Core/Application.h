#pragma once
#include "PiratesEngine/Events/ApplicationEvent.h"
#include "Window.h"
#include "PiratesEngine/ImGui/ImGuiLayer.h"
#include "LayerStack.h"
#include "PiratesEngine/Renderer/Shader.h"
#include "PiratesEngine/ImGui/ImGuiLayer.h"
#include "PiratesEngine/Renderer/Buffer.h"
#include "PiratesEngine/Renderer/OrthoGraphicCamera.h"
#include "PiratesEngine/Core/TimeStep.h"

#include "PiratesEngine/Renderer/VertexArray.h"

namespace Pirates {

	class PIRATES_API Application 
	{
	public:
		Application();
		virtual ~Application();
		void Run();

		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		std::unique_ptr<Window> m_Window;
		std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;
		bool m_Maximized = false;
		float m_LastFrameTime = 0.0f;
	private:
		 static Application* s_Instance;
	};
	Application* CreateApplication();
}