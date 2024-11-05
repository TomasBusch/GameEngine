#pragma once

#ifdef WIN_32
	#define OPENGL_API
	//#define VULKAN_API
	//#define D3D12_API
	//#define D3D11_API
#elif LINUX
	#define OPENGL_API
	//#define VULKAN_API
#elif MAC_OS
	#define VULKAN_API
	//#define METAL_API
#elif ANDROID
	#define VULKAN_API
#endif