#pragma once


#ifdef FLO_PLATFORM_WINDOWS
	#if FLO_DYNAMIC_LINK
		#ifdef FLO_BUILD_DLL
			#define FLONGO_API __declspec(dllexport)
		#else
			#define FLONGO_API __declspec(dllimport)
		#endif
	#else
		#define FLONGO_API
	#endif
#else 
	#error Flongo only supports Windows!
#endif

#ifdef FLO_DEBUG
	#define FLO_ENABLE_ASSERTS
#endif

#ifdef FLO_ENABLE_ASSERTS
	#define FLO_ASSERT(x, ...) { if(!(x)) { FLO_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FLO_CORE_ASSERT(x, ...) { if(!(x)) { FLO_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FLO_ASSERT(x, ...)
	#define FLO_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define FLO_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)