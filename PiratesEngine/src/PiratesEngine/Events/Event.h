#pragma once

#include "PiratesEngine/Core/Core.h"

#include "PEPCH.h"


namespace Pirates {
	/*events in Pirates Currently blocking means when an event occuer it immediatly gets dispathced   */
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
	enum EventCatgory
	{
		None = 0,
		EventCatgoryApplication = BIT(0),
		EventCatgoryInput = BIT(1),
		EventCatgoryKeyBoard = BIT(2),
		EventCatgoryMouse = BIT(3),
		EventCatgoryMouseButton = BIT(4)
	};
#define EVENT_CLASS_TYPE(type) static EventType     GetStaticType() { return EventType::##type; }\
								virtual EventType   GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}


	class PIRATES_API Event 
	{
		friend class EventDispatcher;
	public:
		virtual  EventType GetEventType() const = 0;
		virtual const char* GetName()     const = 0;
		virtual int GetCategoryFlags()	  const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool m_Handled = false;
		inline bool IsInCategory(EventCatgory category)
		{
			return GetCategoryFlags() & category;
		}

	};
	class EventDispatcher 
	{
		template<typename T>
		using Eventfn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : m_Event(event) {}

		template<typename T>
		bool DisPatch(Eventfn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return true;
		}


	private:
		Event& m_Event;

	};
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}