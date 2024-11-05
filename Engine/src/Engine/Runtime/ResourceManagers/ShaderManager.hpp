#pragma once
#include "pch.hpp"


namespace Engine::Resource {
	class ShaderManager {
	public:
		//ShaderManager(ShaderManager& other) = delete;
		//void operator=(const ShaderManager& other) = delete;

		void loadFile(std::filesystem::path filepath);
	private:
		inline static ShaderManager* g_Instance = nullptr;
		inline static std::mutex s_mutex;
	protected:
		ShaderManager() {};
		~ShaderManager() {};
	};
}