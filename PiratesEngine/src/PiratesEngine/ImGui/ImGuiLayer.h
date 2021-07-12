#pragma once
#include "PEPCH.h"
#include "PiratesEngine/Core/Window.h"
#include "PiratesEngine/Core/Layer.h"
#include "PiratesEngine/Events/KeyEvent.h"
#include "PiratesEngine/Events/MouseEvent.h"
#include "PiratesEngine/Events/ApplicationEvent.h"

namespace Pirates
{

	class PIRATES_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

	    virtual	void OnAttach()override;
		virtual	void OnDetach()override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;

	};



}