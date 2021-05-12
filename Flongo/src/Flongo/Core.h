#pragma once

#ifdef FLO_PLATFORM_WINDOWS
	#ifdef FLO_BUILD_DLL
		#define FLONGO_API __declspec(dllexport)
	#else
		#define FLONGO_API __declspec(dllimport)
	#endif
#else 
	#error Flongo only supports Windows!
#endif

#ifdef FLO_ENABLE_ASSERTS
	#define FLO_ASSERT(x, ...) { if(!(x)) { FLO_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
	#define FLO_CORE_ASSERT(x, ...) { if(!(x)) { FLO_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak; } }
#else
	#define FLO_ASSERT(x, ...)
	#define FLO_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)