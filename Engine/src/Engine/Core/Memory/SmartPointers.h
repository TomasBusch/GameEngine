#pragma once

#include "pch.h"

namespace Engine {

	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T, typename ... ArgsT>
	constexpr Scope<T> CreateScope(ArgsT&& ... args)
	{
		return std::make_unique<T>(std::forward<ArgsT>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T, typename ... ArgsT>
	constexpr Ref<T> CreateRef(ArgsT&& ... args)
	{
		return std::make_shared<T>(std::forward<ArgsT>(args)...);
	}

}