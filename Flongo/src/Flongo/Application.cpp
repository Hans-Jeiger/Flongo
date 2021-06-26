#include "flopch.h"
#include "Application.h"

#include "Flongo/Log.h"
#include "Input.h"

#include <glad/glad.h>
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

		ImGuiLayer = new Flongo::ImGuiLayer();
		pushOverlay(ImGuiLayer);


		vertexArray.reset(VertexArray::create());
		

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f,  0.0f, 0.8f, 0.1f, 0.7f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.1f, 0.3f, 0.6f, 1.0f,
			 0.0f,  0.5f,  0.0f, 0.4f, 0.7f, 0.3f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::create(vertices, sizeof(vertices)));

		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "position" },
			{ ShaderDataType::Float4, "color" }
		};

		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);


		uint32_t indices[3] = { 0, 1, 2 };
	
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->setIndexBuffer(indexBuffer);

		squareVA.reset(VertexArray::create());

		float squareVertices[3 * 4] =
		{
			-0.5f, -0.5f,  0.0f,
			 0.5f, -0.5f,  0.0f,
			 0.5f,  0.5f,  0.0f,
			-0.5f,  0.5f,  0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::create(squareVertices, sizeof(squareVertices)));

		squareVB->setLayout({
			{ ShaderDataType::Float3, "position" }
			});
		squareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<IndexBuffer> squareIB; 
		squareIB.reset(IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVA->setIndexBuffer(squareIB);

		std::string vertexSrc =
			R"(
				#version 330 core
				
				layout(location = 0) in vec3 position;
				layout(location = 1) in vec4 color;
				
				out vec3 v_position;
				out vec4 v_color;

				void main()
				{
					v_position = position;
					v_color = color;
					gl_Position = vec4(position, 1.0);
				}
			)";

		std::string fragmentSrc =
			R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				
				in vec3 v_position;
				in vec4 v_color;


				void main()
				{
					color = vec4(v_position * 0.5 + 0.5, 1.0);
					color = v_color;
				}
			)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));



		std::string vertexSrc2 =
			R"(
				#version 330 core
				
				layout(location = 0) in vec3 position;
				
				out vec3 v_position;

				void main()
				{
					v_position = position;
					gl_Position = vec4(position, 1.0);
				}
			)";

		std::string fragmentSrc2 =
			R"(
				#version 330 core
				
				layout(location = 0) out vec4 color;
				
				in vec3 v_position;

				void main()
				{
					color = vec4(0.2, 0.3, 0.8, 1.0);
				}
			)";

		shader2.reset(new Shader(vertexSrc2, fragmentSrc2));
	}

	Application::~Application()
	{

	}

	void Application::run()
	{
		while (running)
		{
			glClearColor(0.1f, 0.11f, 0.12f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader2->bind();
			squareVA->bind();
			glDrawElements(GL_TRIANGLES, squareVA->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			shader->bind();
			vertexArray->bind();
			glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack)
				layer->onUpdate();

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