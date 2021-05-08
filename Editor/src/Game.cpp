
#include <Flongo.h>

class Game : public Flongo::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};

Flongo::Application* Flongo::createApplication()
{
	return new Game();
}