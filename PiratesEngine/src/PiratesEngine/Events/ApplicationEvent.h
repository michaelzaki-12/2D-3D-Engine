#pragma once
#include "Event.h"
#include "PEPCH.h"


namespace Pirates {
	class PIRATES_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_CLASS_TYPE(WindowClose);
		EVENT_CLASS_CATEGORY(EventCatgory::EventCatgoryApplication);
		
	};
	class PIRATES_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCatgory::EventCatgoryApplication)
	};
	class PIRATES_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}
		EVENT_CLASS_TYPE(AppUpdate);
		EVENT_CLASS_CATEGORY(EventCatgoryApplication)

	};
	class PIRATES_API AppRenderEvent : public Event
	{
		AppRenderEvent() {}
		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCatgoryApplication);

	};

	class PIRATES_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent::WindowResizeEvent(unsigned int width, unsigned int height) : M_Width(width), M_Height(height) {}
		~WindowResizeEvent() {}
		inline unsigned int GetWidth() { return M_Width; }
		inline unsigned int GetHeight() { return M_Height; }
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << "(" << M_Width << "," << M_Height << ")";
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize);
		EVENT_CLASS_CATEGORY(EventCatgory::EventCatgoryApplication);


	private:
		unsigned int M_Width, M_Height;

	};


}

