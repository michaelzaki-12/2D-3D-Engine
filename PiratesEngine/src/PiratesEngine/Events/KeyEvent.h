#pragma once
#include "Event.h"

#include "PEPCH.h"



namespace Pirates {

	class PIRATES_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCatgoryKeyBoard | EventCatgoryInput)
	protected:
		KeyEvent(int Keycode) : m_KeyCode(Keycode) {}

		int m_KeyCode;


	};
	class PIRATES_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int KeyCode, int RepeatCount) : KeyEvent(KeyCode), m_RepeatCount(RepeatCount) {}
		inline int GetRepeatCount() const { return m_RepeatCount; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyPressedEvent" << m_KeyCode << " (" << m_RepeatCount << "Repeats)";
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyPressed; }
		virtual EventType GetEventType() const override {return GetStaticType(); }
		virtual const char* GetName() const override {return "KeyPressed";}


		//EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_RepeatCount;

	};

	class PIRATES_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int KeyCode) : KeyEvent(KeyCode){}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyPressed"; }
		
		//EVENT_CLASS_TYPE(KeyReleased);
	};

	class  KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int KeyCode) : KeyEvent(KeyCode) {}
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "keyTypedEvent" << m_KeyCode;
			return ss.str();
		}

		static EventType GetStaticType() { return EventType::KeyTyped; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyTyped"; }


		//EVENT_CLASS_TYPE(KeyTyped);

	};


}