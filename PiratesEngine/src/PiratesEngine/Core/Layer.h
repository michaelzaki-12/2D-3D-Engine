#pragma once

#include "Core.h"
#include "PiratesEngine/Core/TimeStep.h"
#include "PiratesEngine/Events/Event.h"
namespace Pirates
{
	class PIRATES_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach();
		virtual void OnDetach();
		virtual void OnUpdate(TimeStep ts){}
		virtual void OnImGuiRender() {}
		
		virtual void OnEvent(Event& event);
	
		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;

	};

}