#pragma once
#include "Event.h"

#include "PEPCH.h"


namespace Pirates {
	//Moving
	class PIRATES_API MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float xpos, float ypos) : m_MouseX(xpos), m_MouseY(ypos) {}
		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent" << m_MouseX << "," << m_MouseY;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseMoved; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseMoved"; }


		//EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCatgoryMouse | EventCatgoryInput);


	private:
		float m_MouseX, m_MouseY;
	};

	// Scrolling
	class PIRATES_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xoffset, float yoffset) : m_ScrolledX(xoffset),m_ScrolledY(yoffset) {}
		inline float GetXOffSet() const { return m_ScrolledX; }
		inline float GetYOffSet() const { return m_ScrolledY; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent" << m_ScrolledX << "," << m_ScrolledY;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::MouseScrolled; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseScrolled"; }
	
		//EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCatgoryMouse | EventCatgoryInput);

	private:
		float m_ScrolledX, m_ScrolledY;
	};

	//Button Event
	class PIRATES_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return m_Button; }
		EVENT_CLASS_CATEGORY(EventCatgoryMouse | EventCatgoryInput);



	protected:
		MouseButtonEvent(int Button) : m_Button(Button) {}

		int m_Button;

	};




	//Presseing
	class PIRATES_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int Button) : MouseButtonEvent(Button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MousePressedEvent" << m_Button;
			return ss.str();
		}
		static EventType GetStaticType() { return EventType::MouseButtonPressed; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MousePressed"; }

		//EVENT_CLASS_TYPE(MouseButtonPressed);

	};
	//Releaseing
	class PIRATES_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int Button) : MouseButtonEvent(Button) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseReleasedEvent" << m_Button;
			return ss.str();
		}
		static EventType GetStaticType() { return EventType::MouseButtonReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "MouseRelease"; }
		//EVENT_CLASS_TYPE(MouseButtonReleased);
	};


}



