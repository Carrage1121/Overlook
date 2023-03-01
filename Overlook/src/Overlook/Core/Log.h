#pragma once

#include "Overlook/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Overlook {

	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}


//Core log macros
#define OL_CORE_TRACE(...) :: Overlook::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OL_CORE_INFO(...)  :: Overlook::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OL_CORE_WARN(...)  :: Overlook::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OL_CORE_ERROR(...) :: Overlook::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OL_CORE_CRITICAL(...) ::Overlook::Log::GetCoreLogger()->critical(__VA_ARGS__)

//Client log macros
#define OL_TRACE(...) :: Overlook::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OL_INFO(...)  :: Overlook::Log::GetClientLogger()->info(__VA_ARGS__)
#define OL_WARN(...)  :: Overlook::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OL_ERROR(...) :: Overlook::Log::GetClientLogger()->error(__VA_ARGS__)
#define OL_CRITICAL(...)      ::Overlook::Log::GetClientLogger()->critical(__VA_ARGS__)