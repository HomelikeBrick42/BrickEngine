#pragma once

#ifdef BRICKENGINE_PLATFORM_WINDOWS
	#ifdef BRICKENGINE_BUILD_DLL
		#define BRICKENGINE_API __declspec(dllexport)
	#else
		#define BRICKENGINE_API __declspec(dllimport)
	#endif
#else
	#error BrickEngine Only Supports Windows!
#endif
