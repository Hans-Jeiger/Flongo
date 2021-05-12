#pragma once

#ifdef FLO_PLATFORM_WINDOWS

extern Flongo::Application* Flongo::createApplication();

int main(int argc, char** argv)
{
	Flongo::Log::init();
	FLO_CORE_WARN("Initialized a cute little core log! :)");
	int a = 5;
	FLO_INFO("Var={0}", a);
	auto app = Flongo::createApplication();
	app->run();
	delete app;
	return 0;
}

#endif
