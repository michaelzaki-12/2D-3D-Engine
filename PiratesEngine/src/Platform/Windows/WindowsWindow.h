#pragma once
#include "PiratesEngine/Renderer/GraphicsContext.h"
#include "PiratesEngine/Core/Window.h"
#include <GLFW/glfw3.h>

namespace Pirates {
	class  WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallBack(const EventCallBackFn& callback)  override  {m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline void* GetNativeWindow() const { return m_Window; };

	private:
		virtual void  Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallBackFn EventCallback;
		};
		WindowData m_Data;
	};
}
