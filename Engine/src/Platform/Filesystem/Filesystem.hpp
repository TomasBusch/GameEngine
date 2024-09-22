#pragma once
#include "pch.h"

namespace Engine::Filesystem {

	::std::array<> mount_points;

	Open(const std::string& path);
	Read();
	Write();
	Close();
}