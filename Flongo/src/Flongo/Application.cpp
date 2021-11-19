#include "flopch.h"
#include "Application.h"

#include "Flongo/Log.h"

#include <imgui.h>


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
		window->setVSync(true);

		ImGuiLayer = new Flongo::ImGuiLayer();
		pushOverlay(ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (running)
		{
			auto time =  std::chrono::system_clock::now();
			std::chrono::duration<float> duration = time - lastFrameTime;
			Timestep timestep = duration.count();
			lastFrameTime = time;

			for (Layer* layer : layerStack)
				layer->onUpdate(timestep);

			ImGuiLayer->begin();
			for (Layer* layer : layerStack)
				layer->onImGuiRender();
			ImGuiLayer->end();

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