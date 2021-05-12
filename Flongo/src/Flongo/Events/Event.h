#pragma once

#include "flopch.h"
#include "Flongo/Core.h"



namespace Flongo
{
	/*
	Events in flongo are currently blocking, meaning when an event occurs it immediately
	gets dispatched and must be dealt with right then and there. for the future, a better
	strategy might be to buffer events in an event bus and process them during the "event"
	part of the update stage.
	*/

	enum class EventType
	{
		None = 0,
		// Window events
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		// App events
		AppTick, AppUpdate, AppRender,
		//Key events
		KeyPressed, KeyReleased,
		//Mouse events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4),
	};

#define EVENT_CLASS_TYPE(type)	static EventType getStaticType() { return EventType::##type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class FLONGO_API Event
	{
		friend class EventDispatcher;
	
	public:
		virtual EventType getEventType() const = 0;
		virtual const char* getName() const = 0;
		virtual int getCategoryFlags() const = 0;
		virtual std::string toString() const { return getName(); }

		inline bool isInCategory(EventCategory category)
		{
			return getCategoryFlags() & category;
		}

	protected:
		bool handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: event(event)
		{
		}

		template<typename T>
		bool dispatch(EventFn<T> func)
		{
			if (event.getEventType() == T::getStaticType())
			{
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator << (std::ostream& os, const Event& e)
	{
		return os << e.toString();
	}
}