#include <flopch.h>
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Flongo
{
	RendererAPI* RenderCommand::s_rendererAPI = new OpenGLRendererAPI;
}