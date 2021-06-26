#include "flopch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Flongo/Core.h"
#include "Flongo/Log.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Flongo
{
	VertexBuffer* VertexBuffer::create(float* vertices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None: FLO_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		}

		FLO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::getAPI())
		{
		case RendererAPI::None: FLO_CORE_ASSERT(false, "RendererAPI::None is not supported!");
			return nullptr;
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, size);
		}

		FLO_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}