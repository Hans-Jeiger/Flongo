
#include <Flongo.h>

#include "imgui/imgui.h"

class ExampleLayer : public Flongo::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), orthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition({0.0f, 0.0f, 0.0f})
	{
		vertexArray.reset(Flongo::VertexArray::create());

		float vertices[3 * 7] =
		{
			-0.5f, -0.5f,  0.0f, 0.8f, 0.1f, 0.7f, 1.0f,
			 0.5f, -0.5f,  0.0f, 0.1f, 0.3f, 0.6f, 1.0f,
			 0.0f,  0.5f,  0.0f, 0.4f, 0.7f, 0.3f, 1.0f
		};

		std::shared_ptr<Flongo::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Flongo::VertexBuffer::create(vertices, sizeof(vertices)));

		Flongo::BufferLayout layout =
		{
			{ Flongo::ShaderDataType::Float3, "position" },
			{ Flongo::ShaderDataType::Float4, "color" }
		};

		vertexBuffer->setLayout(layout);
		vertexArray->addVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		std::shared_ptr<Flongo::IndexBuffer> indexBuffer;
		indexBuffer.reset(Flongo::IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertexArray->setIndexBuffer(indexBuffer);

		squareVA.reset(Flongo::VertexArray::create());

		float squareVertices[3 * 4] =
		{
			-0.6f, -0.6f,  0.6f,
			 0.6f, -0.6f,  0.6f,
			 0.6f,  0.6f,  0.6f,
			-0.6f,  0.6f,  0.6f
		};

		std::shared_ptr<Flongo::VertexBuffer> squareVB;
		squareVB.reset(Flongo::VertexBuffer::create(squareVertices, sizeof(squareVertices)));

		squareVB->setLayout({
			{ Flongo::ShaderDataType::Float3, "position" }
			});
		squareVA->addVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		std::shared_ptr<Flongo::IndexBuffer> squareIB;
		squareIB.reset(Flongo::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		squareVA->setIndexBuffer(squareIB);

		std::string vertexSrc =
			R"(
				#version 330 core
				
				layout(location = 0) in vec3 position;
				layout(location = 1) in vec4 color;

				uniform mat4 u_viewProjection;
				
				out vec3 v_position;
				out vec4 v_color;

				void main()
				{
					v_position = position;
					v_color = color;
					gl_Position = u_viewProjection * vec4(position, 1.0);
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

		shader.reset(new Flongo::Shader(vertexSrc, fragmentSrc));



		std::string vertexSrc2 =
			R"(
				#version 330 core
				
				layout(location = 0) in vec3 position;

				uniform mat4 u_viewProjection;				

				out vec3 v_position;

				void main()
				{
					v_position = position;
					gl_Position = u_viewProjection * vec4(position, 1.0);
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

		shader2.reset(new Flongo::Shader(vertexSrc2, fragmentSrc2));
	}

	void onUpdate(Flongo::Timestep timestep) override
	{

		FLO_TRACE("Delta time: ms {0}, s {1}", timestep.getMilliseconds(), timestep.getSeconds());

		if (Flongo::Input::isKeyPressed(FLO_KEY_LEFT))
			cameraPosition.x -= cameraSpeed * timestep;

		if (Flongo::Input::isKeyPressed(FLO_KEY_RIGHT))
			cameraPosition.x += cameraSpeed * timestep;

		if (Flongo::Input::isKeyPressed(FLO_KEY_UP))
			cameraPosition.y += cameraSpeed * timestep;

		if (Flongo::Input::isKeyPressed(FLO_KEY_DOWN))
			cameraPosition.y -= cameraSpeed * timestep;


		if (Flongo::Input::isKeyPressed(FLO_KEY_A))
			cameraRotation += cameraRotationSpeed * timestep;

		if (Flongo::Input::isKeyPressed(FLO_KEY_D))
			cameraRotation -= cameraRotationSpeed * timestep;


		Flongo::RenderCommand::setClearColor({ 0.1f, 0.11f, 0.12f, 1 });
		Flongo::RenderCommand::clear();

		orthographicCamera.setPosition(cameraPosition);
		orthographicCamera.setRotation(cameraRotation);

		Flongo::Renderer::beginScene(orthographicCamera);

		Flongo::Renderer::submit(shader2, squareVA);
		Flongo::Renderer::submit(shader, vertexArray);

		Flongo::Renderer::endScene();
	}
	virtual void onImGuiRender() override
	{

	}

	void onEvent(Flongo::Event& event) override
	{

	}

private:
	std::shared_ptr<Flongo::Shader> shader;
	std::shared_ptr<Flongo::Shader> shader2;
	std::shared_ptr<Flongo::VertexArray> vertexArray;
	std::shared_ptr<Flongo::VertexArray> squareVA;

	Flongo::OrthographicCamera orthographicCamera;
	glm::vec3 cameraPosition;
	float cameraSpeed = 5.0f;
	float cameraRotation = 0.0f;
	float cameraRotationSpeed = 180.0f;
};

class Game : public Flongo::Application
{
public:
	Game()
	{
		pushLayer(new ExampleLayer());
	}

	~Game()
	{

	}
};

Flongo::Application* Flongo::createApplication()
{
	return new Game();
}

