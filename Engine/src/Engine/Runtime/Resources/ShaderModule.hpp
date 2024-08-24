#pragma once
#include "pch.hpp"


namespace Engine::Resource {
	class ShaderModule {
	public:
		ShaderModule(ShaderModule& other) = delete;
		void operator=(const ShaderModule& other) = delete;

		static ShaderModule& Get();

		void LoadFile(std::filesystem::path filepath);
	private:
		inline static ShaderModule* g_Instance = nullptr;
		inline static std::mutex s_mutex;
	protected:
		ShaderModule() {};
		~ShaderModule() {};
	};
}