#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace RuiEngine {
	class RE_API Log
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
#define RE_CORE_ERROR(...)	::RuiEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RE_CORE_WARN(...)	::RuiEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RE_CORE_INFO(...)	::RuiEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RE_CORE_TRACE(...)	::RuiEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RE_CORE_CRITICAL(...)	::RuiEngine::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define RE_ERROR(...)		::RuiEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define RE_WARN(...)		::RuiEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RE_INFO(...)		::RuiEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define RE_TRACE(...)		::RuiEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RE_CRITICAL(...)		::RuiEngine::Log::GetClientLogger()->critical(__VA_ARGS__)