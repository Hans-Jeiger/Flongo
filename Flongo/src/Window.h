#pragma once

#include "flopch.h"

#include "Flongo/Log.h"
#include "Flongo/Core.h"
#include "Flongo/Events/Event.h"


namespace Flongo
{
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(
			const std::string& title = "Flongo Engine",
			unsigned int width = 1280,
			unsigned int height = 720
		) : title(title), width(width), height(height) {}
	};


	class FLONGO_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void onUpdate() = 0;

		virtual unsigned int getWidth() const = 0;
		virtual unsigned int getHeight() const = 0;

		// Window attributes
		virtual void setEventCallback(const EventCallbackFn& callback) = 0;
		virtual void setVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* getNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}