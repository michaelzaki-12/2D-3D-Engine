#pragma once
#include "Core.h"
#include "PEPCH.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Pirates {

	class PIRATES_API Log
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

#define PR_CORE_ERROR(...) ::Pirates::Log::GetCoreLogger()->error(__VA_ARGS__)
#define PR_CORE_INFO(...) ::Pirates::Log::GetCoreLogger()->info(__VA_ARGS__)
#define PR_CORE_TRACE(...) ::Pirates::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define PR_CORE_WARN(...) ::Pirates::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define PR_CLIENT_ERROR(...) ::Pirates::Log::GetClientLogger()->error(__VA_ARGS__)
#define PR_CLIENT_INFO(...) ::Pirates::Log::GetClientLogger()->info(__VA_ARGS__)
#define PR_CLIENT_TRACE(...) ::Pirates::Log::GetClientLogger()->trace(__VA_ARGS__)
#define PR_CLIENT_WARN(...) ::Pirates::Log::GetClientLogger()->warn(__VA_ARGS__)
