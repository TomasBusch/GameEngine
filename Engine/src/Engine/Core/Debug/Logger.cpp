#include "Logger.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Engine::Log {

	Ref<spdlog::logger> Core::Logger;

	void Core::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("client.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");
		Logger = std::make_shared<spdlog::logger>("CLIENT", begin(logSinks), end(logSinks));
		spdlog::register_logger(Logger);
		Logger->set_level(spdlog::level::trace);
		Logger->flush_on(spdlog::level::trace);
	}

	Ref<spdlog::logger> Client::Logger;

	void Client::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("core.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");
		Logger = std::make_shared<spdlog::logger>("CORE", begin(logSinks), end(logSinks));
		spdlog::register_logger(Logger);
		Logger->set_level(spdlog::level::trace);
		Logger->flush_on(spdlog::level::trace);
	}
}