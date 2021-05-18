#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Layers/LayerStack.h"
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

		void pushLayer(Layer* layer);
		void pushOverlay(Layer* overlay);

		inline static Application& get() { return *instance; }
		inline Window& getWindow() { return *window; }

	private:
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window;
		bool running = true;
		LayerStack layerStack;

		static Application* instance;
	};

	// To be defined in client
	Application* createApplication();
}