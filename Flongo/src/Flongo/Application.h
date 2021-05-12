#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Flongo/Events/ApplicationEvent.h"


namespace Flongo
{
	class FLONGO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void onEvent(Event& e);

	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;
	};

	// To be defined in client
	Application* createApplication();
}