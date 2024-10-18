#pragma once
#include "Engine/Core/Base.hpp"

#pragma warning(push, 0)
#include <spdlog/logger.h>
#pragma warning(pop)

namespace Engine{
	class Logger {
	public:
		static void Init();

	public:
		static Ref<::spdlog::logger> m_Core;
		static Ref<::spdlog::logger> m_Client;
	};
}

// Core log macros
#define ENGINE_CORE_TRACE(...)    ::Engine::Logger::m_Core->trace(__VA_ARGS__)
#define ENGINE_CORE_INFO(...)     ::Engine::Logger::m_Core->info(__VA_ARGS__)
#define ENGINE_CORE_WARN(...)     ::Engine::Logger::m_Core->warn(__VA_ARGS__)
#define ENGINE_CORE_ERROR(...)    ::Engine::Logger::m_Core->error(__VA_ARGS__)
#define ENGINE_CORE_CRITICAL(...) ::Engine::Logger::m_Core->critical(__VA_ARGS__)

// Client log macros
#define ENGINE_TRACE(...)         ::Engine::Logger::m_Client->trace(__VA_ARGS__)
#define ENGINE_INFO(...)          ::Engine::Logger::m_Client->info(__VA_ARGS__)
#define ENGINE_WARN(...)          ::Engine::Logger::m_Client->warn(__VA_ARGS__)
#define ENGINE_ERROR(...)         ::Engine::Logger::m_Client->error(__VA_ARGS__)
#define ENGINE_CRITICAL(...)      ::Engine::Logger::m_Client->critical(__VA_ARGS__)