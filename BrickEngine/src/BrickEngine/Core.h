#pragma once

#define GLM_FORCE_CTOR_INIT

#ifdef BRICKENGINE_PLATFORM_WINDOWS
#ifdef BRICKENGINE_DYNAMIC_LINK
	#ifdef BRICKENGINE_BUILD_DLL
		#define BRICKENGINE_API __declspec(dllexport)
	#else
		#define BRICKENGINE_API __declspec(dllimport)
	#endif
#else
	#define BRICKENGINE_API
#endif
#else
	#error BrickEngine Only Supports Windows!
#endif

#ifdef BRICKENGINE_DEBUG
	#define BRICKENGINE_ENABLE_ASSERTS
#endif

#ifdef BRICKENGINE_ENABLE_ASSERTS
	#define BRICKENGINE_ASSERT(x, ...) { if(!(x)) { BRICKENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BRICKENGINE_CORE_ASSERT(x, ...) { if(!(x)) { BRICKENGINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BRICKENGINE_ASSERT(x, ...)
	#define BRICKENGINE_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BRICKENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
