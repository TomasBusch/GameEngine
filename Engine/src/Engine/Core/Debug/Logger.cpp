#include "Logger.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Engine {

	Ref<spdlog::logger> Logger::m_Core;
	Ref<spdlog::logger> Logger::m_Client;

	void Logger::Init()
	{
		std::vector<spdlog::sink_ptr> corelogSinks;
		corelogSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		corelogSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("client.log", true));

		corelogSinks[0]->set_pattern("%^[%T] %n: %v%$");
		corelogSinks[1]->set_pattern("[%T] [%l] %n: %v");
		m_Core = std::make_shared<spdlog::logger>("CLIENT", begin(corelogSinks), end(corelogSinks));
		spdlog::register_logger(m_Core);
		m_Core->set_level(spdlog::level::trace);
		m_Core->flush_on(spdlog::level::trace);

		std::vector<spdlog::sink_ptr> clientlogSinks;
		clientlogSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		clientlogSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("client.log", true));

		clientlogSinks[0]->set_pattern("%^[%T] %n: %v%$");
		clientlogSinks[1]->set_pattern("[%T] [%l] %n: %v");
		m_Client = std::make_shared<spdlog::logger>("CLIENT", begin(clientlogSinks), end(clientlogSinks));
		spdlog::register_logger(m_Client);
		m_Client->set_level(spdlog::level::trace);
		m_Client->flush_on(spdlog::level::trace);
	}
}