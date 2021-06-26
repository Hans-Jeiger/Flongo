#pragma once

#include "Window.h"
#include "Flongo/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Flongo
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void onUpdate() override;
		inline unsigned int getWidth() const override { return data.width; }
		inline unsigned int getHeight() const override { return data.height; }

		// Window attributes
		inline void setEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
		void setVSync(bool enabled) override;
		bool isVSync() const override;

		inline virtual void* getNativeWindow() const override { return window; }

	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();

	private:
		GraphicsContext* context;
		GLFWwindow* window;

		struct WindowData
		{
			std::string title = "";
			unsigned int width = 0, height = 0;
			bool VSync = false;

			EventCallbackFn eventCallback;
		};

		WindowData data;
	};
}