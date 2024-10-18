#pragma once
#include "pch.hpp"

template <typename... Args>
using Callback = std::function<void(Args...)>;

#define MemberCallback(fn) [this](auto&&... args) -> decltype(auto) {  \
	return this->fn(std::forward<decltype(args)>(args)...);            \
}                                                                      \
