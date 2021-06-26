#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Layers/LayerStack.h"
#include "Flongo/Events/ApplicationEvent.h"
#include "Flongo/ImGui/ImGuiLayer.h"

#include "Flongo/Renderer/Shader.h"

#include "Flongo/Renderer/Buffer.h"
#include "Flongo/Renderer/VertexArray.h"

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
		ImGuiLayer* ImGuiLayer;
		bool running = true;
		LayerStack layerStack;

		std::shared_ptr<Shader> shader;
		std::shared_ptr<Shader> shader2;
		std::shared_ptr<VertexArray> vertexArray;

		std::shared_ptr<VertexArray> squareVA;

	private:
		static Application* instance;
	};

	// To be defined in client
	Application* createApplication();
}