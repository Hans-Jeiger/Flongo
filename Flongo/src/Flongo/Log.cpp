#include "flopch.h"
#include "Log.h"

namespace Flongo
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T]  %n: %v%$");

		s_coreLogger = spdlog::stdout_color_mt("FLONKO");
		s_coreLogger->set_level(spdlog::level::trace);

		s_clientLogger = spdlog::stdout_color_mt("APPLICATION");
		s_clientLogger->set_level(spdlog::level::trace);


	}
}