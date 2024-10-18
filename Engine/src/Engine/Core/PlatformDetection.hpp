#pragma once

#ifdef WIN_32
	#define OPENGL
	#define VULKAN
	#define D3D12
	#define D3D11
#elif LINUX
	#define OPENGL
	#define VULKAN
#elif MAC_OS
	#define VULKAN
	#define METAL
#elif ANDROID
	#define VULKAN