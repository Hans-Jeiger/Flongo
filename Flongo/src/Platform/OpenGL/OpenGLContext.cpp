#include "flopch.h"
#include "OpenGLContext.h"
#include "Flongo/Core.h"
#include "Flongo/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Flongo
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: windowHandle(windowHandle)
	{
		FLO_CORE_ASSERT(windowHandle, "windowHandle is null!");
	}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FLO_CORE_ASSERT(status, "Failed to initialize Glad!");


		FLO_CORE_INFO("Vendor: {0}", glGetString(GL_VENDOR));
		FLO_CORE_INFO("OpenGL Info:");
		FLO_CORE_INFO("Renderer: {0}", glGetString(GL_RENDERER));
		FLO_CORE_INFO("Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}