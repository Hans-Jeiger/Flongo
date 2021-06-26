
#include <Flongo.h>

#include "imgui/imgui.h"

class ExampleLayer : public Flongo::Layer
{
public:
	ExampleLayer()
		: Layer("Example") 
	{
		
	}

	void onUpdate() override
	{
		if (Flongo::Input::isKeyPressed(FLO_KEY_TAB))
			FLO_INFO("Tab's friggin pressed broh (game.cpp)");
		//FLO_INFO("ExampleLayer::onUpdate()");
	}

	virtual void onImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::End();
	}

	void onEvent(Flongo::Event& event) override
	{
		//FLO_TRACE("{0}", event);
	}
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