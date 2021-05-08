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