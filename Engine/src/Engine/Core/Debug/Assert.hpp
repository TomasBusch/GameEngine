#pragma once

#include "Logger.hpp"

#if defined(_MSC_VER) // Microsoft Visual Studio (Windows)
#define DEBUGBREAK() __debugbreak()

#elif defined(__GNUC__) || defined(__clang__) // GCC or Clang (Linux, macOS, Unix-like systems)
#if defined(__APPLE__) && defined(__MACH__) // macOS
#define DEBUGBREAK() __builtin_trap()
#elif defined(__i386__) || defined(__x86_64__) // Linux, BSD, Unix on x86/x86_64
#define DEBUGBREAK() __asm__ __volatile__("int $0x03")
#elif defined(__arm__) || defined(__aarch64__) // Linux on ARM
#define DEBUGBREAK() __builtin_trap()
#else // Other platforms
#define DEBUGBREAK() raise(SIGTRAP)
#endif

#else
#include <signal.h> // Fallback for unknown compilers
#define DEBUGBREAK() raise(SIGTRAP)
#endif

#define ENGINE_EXPAND_MACRO(x) x
#define ENGINE_STRINGIFY_MACRO(x) #x

#ifdef DEBUG

#define ENGINE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ENGINE##type##ERROR(msg, __VA_ARGS__); DEBUGBREAK(); } }
#define ENGINE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ENGINE_INTERNAL_ASSERT_NO_MSG(type, check) ENGINE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ENGINE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ENGINE_INTERNAL_ASSERT_GET_MACRO(...) ENGINE_EXPAND_MACRO( ENGINE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ENGINE_INTERNAL_ASSERT_WITH_MSG, ENGINE_INTERNAL_ASSERT_NO_MSG) )

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define ENGINE_ASSERT(...) ENGINE_EXPAND_MACRO( ENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define ENGINE_CORE_ASSERT(...) ENGINE_EXPAND_MACRO( ENGINE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#define ENGINE_BREAK(...) ENGINE_ASSERT(false, __VA_ARGS__)
#define ENGINE_CORE_BREAK(...) ENGINE_CORE_ASSERT(false, __VA_ARGS__)
#else
#define ENGINE_ASSERT(...)
#define ENGINE_CORE_ASSERT(...)

#define ENGINE_BREAK(...)
#define ENGINE_CORE_BREAK(...)
#endif