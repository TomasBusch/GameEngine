#include "ShaderModule.hpp"

#include <shaderc/shaderc.hpp>

namespace Engine::Resource {
	ShaderModule& ShaderModule::Get() 
	{
		std::lock_guard<std::mutex> lock(s_mutex);
		if (g_Instance == nullptr) {
			g_Instance = new ShaderModule();
		}
		return *g_Instance;
	}
	void ShaderModule::LoadFile(std::filesystem::path filepath)
	{

	}

	static shaderc::PreprocessedSourceCompilationResult 
		Preprocess(const std::string& source_name, shaderc_shader_kind kind, const std::string& source) 
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);
		options.SetOptimizationLevel(shaderc_optimization_level_performance);

		shaderc::PreprocessedSourceCompilationResult result = compiler.PreprocessGlsl(source, kind, source_name.c_str(), options);
		
		if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
			//TODO Inform error
		}
		auto begin = result.cbegin();

		return result;
	}

	static shaderc::AssemblyCompilationResult
		CompileToAssembly(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false)
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		if (optimize) {
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		}

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

		shaderc::AssemblyCompilationResult result = compiler.CompileGlslToSpvAssembly(source, kind, source_name.c_str(), options);

		if (result.GetCompilationStatus() != shaderc_compilation_status_success) {
			//TODO Inform error
		}

		return result;
	}

	static shaderc::SpvCompilationResult
		CompileToBinary(const std::string& source_name, shaderc_shader_kind kind, const std::string& source, bool optimize = false) 
	{
		shaderc::Compiler compiler;
		shaderc::CompileOptions options;

		if (optimize) {
			options.SetOptimizationLevel(shaderc_optimization_level_performance);
		}

		options.SetTargetEnvironment(shaderc_target_env_opengl, shaderc_env_version_opengl_4_5);

		shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, kind, source_name.c_str(), options);

		if (module.GetCompilationStatus() != shaderc_compilation_status_success) {
			//TODO: Inform error
		}

		return module;
	}


}