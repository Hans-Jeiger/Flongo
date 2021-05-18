#include "flopch.h"
#include "Application.h"

#include "Flongo/Log.h"

#include <glad/glad.h>

namespace Flongo
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application()
	{
		FLO_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->setEventCallback(BIND_EVENT_FN(Application::onEvent));
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack)
				layer->onUpdate();

			window->onUpdate();
		}
	}

	void Application::onEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::onWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*--it)->onEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::pushLayer(Layer* layer)
	{
		layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::pushOverlay(Layer* layer)
	{
		layerStack.pushOverlay(layer);
		layer->onAttach();
	}

	bool Application::onWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}
}