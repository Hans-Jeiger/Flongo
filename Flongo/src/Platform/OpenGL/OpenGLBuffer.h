#pragma once

#include "Flongo/Renderer/Buffer.h"

namespace Flongo
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual const BufferLayout& getLayout() const override { return layout; }
		virtual void setLayout(const BufferLayout& layout_in) override { layout = layout_in; }

	private:
		uint32_t rendererID;
		BufferLayout layout;
	};



	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t getCount() const { return count; }

	private:
		uint32_t rendererID;
		uint32_t count;
	};
}