#pragma once
#include "Engine/Core/Base.hpp"

#include <spdlog/logger.h>

namespace Engine{

	namespace Client {
		class Logger {
		public:
			static void Init();

			template<typename ...Args>
			inline static void Info(Args&& ...args) {
				s_Logger->info(std::forward<Args>(args...));
			}

			template<typename ...Args>
			inline static void Error(Args&& ...args) {
				s_Logger->error(std::forward<Args>(args...));
			}

			template<typename ...Args>
			inline static void Critical(Args&& ...args) {
				s_Logger->critical(std::forward<Args>(args...));
			}

			template<typename ...Args>
			inline static void Debug(Args&& ...args) {
				s_Logger->debug(std::forward<Args>(args...));
			}

			template<typename ...Args>
			inline static void Warn(Args&& ...args) {
				s_Logger->warn(std::forward<Args>(args...));
			}

		private:
			static Ref<spdlog::logger> s_Logger;
		};

	}
	namespace Core {
		class Logger {
		public:
			static void Init();

			template<typename ...Args>
			inline static void Info(Args&& ...args) {
				s_Logger->info(std::forward<Args>(args)...);
			}

			template<typename ...Args>
			inline static void Error(Args&& ...args) {
				s_Logger->error(std::forward<Args>(args)...);
			}

			template<typename ...Args>
			inline static void Critical(Args&& ...args) {
				s_Logger->critical(std::forward<Args>(args)...);
			}

			template<typename ...Args>
			inline static void Debug(Args&& ...args) {
				s_Logger->debug(std::forward<Args>(args)...);
			}

			template<typename ...Args>
			inline static void Warn(Args&& ...args) {
				s_Logger->warn(std::forward<Args>(args)...);
			}

		private:
			static Ref<spdlog::logger> s_Logger;
		};
	}
}