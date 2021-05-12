#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace Flongo
{
	class FLONGO_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_clientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}


// Core log macros

#define FLO_CORE_TRACE(...)      ::Flongo::Log::getCoreLogger()->trace(__VA_ARGS__)
#define FLO_CORE_INFO(...)       ::Flongo::Log::getCoreLogger()->info(__VA_ARGS__)
#define FLO_CORE_WARN(...)       ::Flongo::Log::getCoreLogger()->warn(__VA_ARGS__)
#define FLO_CORE_ERROR(...)      ::Flongo::Log::getCoreLogger()->error(__VA_ARGS__)
#define FLO_CORE_CRITICAL(...)   ::Flongo::Log::getCoreLogger()->critical(__VA_ARGS__)


// Client log macros

#define FLO_TRACE(...)           ::Flongo::Log::getClientLogger()->trace(__VA_ARGS__)
#define FLO_INFO(...)            ::Flongo::Log::getClientLogger()->info(__VA_ARGS__)
#define FLO_WARN(...)            ::Flongo::Log::getClientLogger()->warn(__VA_ARGS__)
#define FLO_ERROR(...)           ::Flongo::Log::getClientLogger()->error(__VA_ARGS__)
#define FLO_CRITICAL(...)        ::Flongo::Log::getClientLogger()->critical(__VA_ARGS__)
