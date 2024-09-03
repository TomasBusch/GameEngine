#pragma once
#include "Engine/Core/Base.hpp"

#pragma warning(push, 0)
#include <spdlog/logger.h>
#pragma warning(pop)

namespace Engine::Log{
	class Core {
	public:
		static void Init();

	public:
		static Ref<::spdlog::logger> Logger;
	};

	class Client {
	public:
		static void Init();

	public:
		static Ref<::spdlog::logger> Logger;
	};
}

// Core log macros
#define ENGINE_CORE_TRACE(...)    ::Engine::Log::Core::Logger->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)     ::Engine::Log::Core::Logger->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)     ::Engine::Log::Core::Logger->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)    ::Engine::Log::Core::Logger->error(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...) ::Engine::Log::Core::Logger->critical(__VA_ARGS__)

// Client log macros
#define ENGINE_TRACE(...)         ::Engine::Log::Client::Logger->trace(__VA_ARGS__)
#define ENGINE_INFO(...)          ::Engine::Log::Client::Logger->info(__VA_ARGS__)
#define ENGINE_WARN(...)          ::Engine::Log::Client::Logger->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)         ::Engine::Log::Client::Logger->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...)      ::Engine::Log::Client::Logger->critical(__VA_ARGS__)