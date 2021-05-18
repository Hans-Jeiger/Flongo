
#include <Flongo.h>

class ExampleLayer : public Flongo::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void onUpdate() override
	{
		FLO_INFO("ExampleLayer::onUpdate()");
	}

	void onEvent(Flongo::Event& event) override
	{
		FLO_TRACE("{0}", event);
	}
};

class Game : public Flongo::Application
{
public:
	Game()
	{
		pushLayer(new ExampleLayer());
		pushOverlay(new Flongo::ImGuiLayer());
	}

	~Game()
	{

	}
};

Flongo::Application* Flongo::createApplication()
{
	return new Game();
}