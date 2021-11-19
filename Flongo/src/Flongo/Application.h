#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Layers/LayerStack.h"
#include "Flongo/Events/ApplicationEvent.h"
#include "Flongo/ImGui/ImGuiLayer.h"

#include "Flongo/Renderer/Shader.h"

#include "Flongo/Renderer/Renderer.h"
#include "Flongo/Core/Timestep.h"

namespace Flongo
{
	class Application
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
	
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* ImGuiLayer;
		bool running = true;
		LayerStack layerStack;
		std::chrono::system_clock::time_point lastFrameTime = std::chrono::system_clock::now();

	private:
		static Application* instance;
	};

	// To be defined in client
	Application* createApplication();
}