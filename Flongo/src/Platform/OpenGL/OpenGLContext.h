#pragma once

#include "Flongo/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Flongo
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		~OpenGLContext();

		virtual void init() override;
		virtual void swapBuffers() override;

	private:
		GLFWwindow* windowHandle;
	};
}