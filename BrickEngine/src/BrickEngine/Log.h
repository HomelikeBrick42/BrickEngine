#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace BrickEngine {

	class BRICKENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define BRICKENGINE_CORE_TRACE(...)		::BrickEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BRICKENGINE_CORE_INFO(...)		::BrickEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BRICKENGINE_CORE_WARN(...)		::BrickEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BRICKENGINE_CORE_ERROR(...)		::BrickEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BRICKENGINE_CORE_FATAL(...)		::BrickEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BRICKENGINE_TRACE(...)			::BrickEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define BRICKENGINE_INFO(...)			::BrickEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define BRICKENGINE_WARN(...)			::BrickEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BRICKENGINE_ERROR(...)			::BrickEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define BRICKENGINE_FATAL(...)			::BrickEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
