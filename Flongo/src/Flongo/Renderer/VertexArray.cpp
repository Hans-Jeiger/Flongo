#include "flopch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Flongo
{
	VertexArray* VertexArray::create()
	{
		switch (Renderer::getAPI())
		{
			case RendererAPI::None: FLO_CORE_ASSERT(false, "RendererAPI::None is not supported!");
				return nullptr;
			case RendererAPI::OpenGL: return new OpenGLVertexArray();
		}

		FLO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}