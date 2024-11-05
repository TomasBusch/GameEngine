#pragma once
#include "pch.hpp"


namespace Engine {
	struct ImageAsset {

		enum class ImageFormat {

		};

		std::string filePath;
		void* image_data;
	};
}