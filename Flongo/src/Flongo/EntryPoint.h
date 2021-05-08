#pragma once

#ifdef FLO_PLATFORM_WINDOWS

extern Flongo::Application* Flongo::createApplication();

int main(int argc, char** argv)
{
	printf("Flongo Engine :)\n");
	auto app = Flongo::createApplication();
	app->run();
	delete app;
	return 0;
}

#endif
