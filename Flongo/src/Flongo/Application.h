#pragma once
#include "Core.h"

namespace Flongo
{
	class FLONGO_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application* createApplication();
}