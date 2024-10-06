# CPM Package Lock

#gtest
	CPMAddPackage(
	  NAME googletest
	  VERSION 1.15.2
	  GITHUB_REPOSITORY google/googletest
	  OPTIONS 
	  "INSTALL_GTEST FALSE" 
	  "BUILD_GMOCK TRUE"
	  "gtest_force_shared_crt" 
	)

#zlib
	find_package(ZLIB)
	if(NOT ZLIB_FOUND)

		CPMAddPackage(
		  NAME zlib
		  VERSION 1.3.1
		  GITHUB_REPOSITORY madler/zlib
		  OPTIONS 
			"ZLIB_BUILD_TESTS OFF"
			"ZLIB_BUILD_EXAMPLES OFF"
		)

		set(ZLIB_CUSTOM_INCLUDES $<BUILD_INTERFACE:${zlib_SOURCE_DIR}> $<BUILD_INTERFACE:${zlib_BINARY_DIR}>)
		#Remove incorrect include directories
		set_target_properties(zlib PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "")
		set_target_properties(zlibstatic PROPERTIES INTERFACE_INCLUDE_DIRECTORIES "")
		#Add our own relative include directories
		target_include_directories(zlib PUBLIC ${ZLIB_CUSTOM_INCLUDES})
		target_include_directories(zlibstatic PUBLIC ${ZLIB_CUSTOM_INCLUDES})

		add_library(ZLIB::zlib ALIAS zlib)
		add_library(ZLIB::zlibstatic ALIAS zlibstatic)
		if(NOT TARGET ZLIB::ZLIB)
			add_library(ZLIB::ZLIB ALIAS zlibstatic)
		endif()

		#Set variables expected by FindZLIB
		set(ZLIB_FOUND TRUE)
		set(ZLIB_LIBRARY ZLIB::zlib)
		set(ZLIB_LIBRARIES ZLIB::zlib)
		set(ZLIB_INCLUDE_DIR "$<BUILD_INTERFACE:${zlib_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${zlib_BINARY_DIR}>")
		set(ZLIB_INCLUDE_DIRS "$<BUILD_INTERFACE:${zlib_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${zlib_BINARY_DIR}>")
	endif()

#OpenGL
	find_package(OpenGL REQUIRED)

#Vulkan
	#Select Vulkan Components
	set(VULKAN_COMPONENTS
		"glslc"
		"glslangValidator"
		"glslang"
		"shaderc_combined"
		"SPIRV-Tools"
		#"dxc"
	)

	#Find Vulkan
	find_package(Vulkan REQUIRED COMPONENTS "${VULKAN_COMPONENTS}")
	if(NOT Vulkan_FOUND)
		message(FATAL_ERROR "VulkanSDK could not be found, make sure that VulkanSDK is installed!")
	else()
		message(STATUS "Vulkan: Version ${Vulkan_VERSION}")
		if(TARGET Vulkan::Vulkan)
			message(WARNING "Vulkan::Vulkan found")
		endif()
		if(TARGET Vulkan::glslc)
			message(WARNING "Vulkan::glslc found")
		endif()
		if(TARGET Vulkan::Headers)
			message(WARNING "Vulkan::Headers found")
		endif()
		if(TARGET Vulkan::glslangValidator)
			message(WARNING "Vulkan::glslangValidator found")
		endif()
		if(TARGET Vulkan::glslang)
			add_library(glslang ALIAS Vulkan::glslang)
			message(WARNING "Vulkan::glslang found")
		endif()
		if(TARGET Vulkan::shaderc_combined)
			message(WARNING "Vulkan::shaderc_combined found")
		endif()
		if(TARGET Vulkan::SPIRV-Tools)
			add_library(SPIRV-Tools ALIAS Vulkan::SPIRV-Tools)
			message(WARNING "Vulkan::SPIRV-Tools found")
		endif()
		if(TARGET Vulkan::MoltenVK)
			message(WARNING "Vulkan::MoltenVK found")
		endif()
		if(TARGET Vulkan::volk)
			message(WARNING "Vulkan::volk found")
		endif()
		if(TARGET Vulkan::dxc_lib)
			message(WARNING "Vulkan::dxc_lib found")
		endif()
		if(TARGET Vulkan::dxc_exe)
			message(WARNING "Vulkan::dxc_exe found")
		endif()
	endif()

#SPIRV-Cross
	CPMAddPackage(
	NAME SPIRV-Cross
	VERSION 1.3.290.0
	GIT_TAG vulkan-sdk-1.3.290.0
	GITHUB_REPOSITORY KhronosGroup/SPIRV-Cross
	)

#SDL2
	CPMAddPackage(
	  NAME SDL2
	  VERSION 2.30.7
	  GIT_TAG release-2.30.7
	  GITHUB_REPOSITORY libsdl-org/SDL
	)

#GFLW
	CPMAddPackage(
	  NAME GLFW
	  VERSION 3.4
	  GIT_TAG 3.4
	  GITHUB_REPOSITORY glfw/glfw
	)

#glad
	find_package(Python COMPONENTS Interpreter REQUIRED)
	#if(DEFINED ENV{VIRTUAL_ENV} OR DEFINED ENV{CONDA_PREFIX})
	#  set(_pip_args)
	#else()
	#  set(_pip_args "--user")
	#endif()
	execute_process(COMMAND ${Python_EXECUTABLE} -m pip install --user jinja2)

	CPMAddPackage(
		NAME glad
		VERSION 2.0.7
		GITHUB_REPOSITORY Dav1dde/glad
		DOWNLOAD_ONLY TRUE
	)
	add_subdirectory("${glad_SOURCE_DIR}/cmake")
	glad_add_library(glad_egl_15 MERGE REPRODUCIBLE API egl:core=1.5)
	glad_add_library(glad_gl_core33 MERGE REPRODUCIBLE API gl:core=3.3)
	glad_add_library(glad_gl_core46 MERGE REPRODUCIBLE API gl:core=4.6)
	glad_add_library(glad_gles1_10 MERGE REPRODUCIBLE API gles1:core=1.0)
	glad_add_library(glad_gles2_32 MERGE REPRODUCIBLE API gles2:core=3.2)
	glad_add_library(glad_glsc2_20 MERGE REPRODUCIBLE API glsc2:core=2.0)
	glad_add_library(glad_glx_14 MERGE REPRODUCIBLE API glx:core=1.4)
	glad_add_library(glad_vulkan13 MERGE REPRODUCIBLE API vulkan=1.3)
	glad_add_library(glad_wgl_10 MERGE REPRODUCIBLE API wgl:core=1.0)

#glm
	CPMAddPackage(
		NAME glm
		VERSION 1.0.1
		GIT_TAG 1.0.1
		GITHUB_REPOSITORY g-truc/glm
		OPTIONS "GLM_ENABLE_CXX_20 TRUE"
	)

#shaderc
#	CPMAddPackage(
#		NAME shaderc
#		VERSION 2024.2
#		GITHUB_REPOSITORY google/shaderc
#		OPTIONS
#		"SHADERC_ENABLE_TESTS FALSE"
#	)


#EnTT
	CPMAddPackage(
	  NAME EnTT
	  VERSION 3.13.2
	  GITHUB_REPOSITORY skypjack/entt
	)
	
#meta
	CPMAddPackage(
	  NAME meta
	  VERSION 1.4.7
	  GITHUB_REPOSITORY skypjack/meta
	  # the project's CMakeLists messes with configuration options
	  DOWNLOAD_ONLY TRUE
	)

	if (meta_ADDED)
	  add_library(meta INTERFACE)
	  target_include_directories(meta INTERFACE ${meta_SOURCE_DIR}/src)
	endif()

#uvw
	CPMAddPackage(
	  NAME uvw
	  VERSION 3.4.0
	  GIT_TAG v3.4.0_libuv_v1.48
	  GITHUB_REPOSITORY skypjack/uvw
	)

#fmtlib
	CPMAddPackage(
	  NAME fmtlib
	  VERSION 10.2.1
	  GIT_TAG 10.2.1
	  GITHUB_REPOSITORY fmtlib/fmt 
)

#spdlog
	CPMAddPackage(
	  NAME spdlog
	  VERSION 1.14.1
	  GITHUB_REPOSITORY gabime/spdlog 
	  OPTIONS "SPDLOG_FMT_EXTERNAL 1"
	)

#FreeType
	CPMAddPackage(
	  NAME freetype
	  GIT_REPOSITORY https://github.com/aseprite/freetype2.git
	  GIT_TAG VER-2-10-0
	  VERSION 2.10.0
	  OPTIONS FT_WITH_ZLIB TRUE
	)

	if (freetype_ADDED)
	  add_library(Freetype::Freetype ALIAS freetype)
	endif()

# ImGui
	CPMAddPackage(
	  NAME imgui
	  VERSION 1.91.1
	  GIT_TAG v1.91.1-docking
	  GITHUB_REPOSITORY ocornut/imgui
	  DOWNLOAD_ONLY TRUE
	)

	# CMakeLists.txt from https://gist.githubusercontent.com/rokups/f771217b2d530d170db5cb1e08e9a8f4
	file(
	  DOWNLOAD
	  "https://gist.githubusercontent.com/rokups/f771217b2d530d170db5cb1e08e9a8f4/raw/4c2c14374ab878ca2f45daabfed4c156468e4e27/CMakeLists.txt"
	  "${imgui_SOURCE_DIR}/CMakeLists.txt"
	  EXPECTED_HASH SHA256=fd62f69364ce13a4f7633a9b50ae6672c466bcc44be60c69c45c0c6e225bb086
	)

	# Options
	set(IMGUI_EXAMPLES FALSE)
	set(IMGUI_DEMO TRUE)
	set(IMGUI_ENABLE_STDLIB_SUPPORT TRUE)
	# FreeType (https://github.com/cpm-cmake/CPM.cmake/wiki/More-Snippets#freetype)
	set(FREETYPE_FOUND TRUE)
	set(FREETYPE_INCLUDE_DIRS "${freetype_SOURCE_DIR}/include")
	set(FREETYPE_LIBRARIES Freetype::Freetype)

	# Add subdirectory
	add_subdirectory(${imgui_SOURCE_DIR} EXCLUDE_FROM_ALL SYSTEM)

#Assimp
	CPMAddPackage(
	  NAME Assimp
	  VERSION 5.4.3
	  GITHUB_REPOSITORY assimp/assimp
	  OPTIONS 
		"ASSIMP_BUILD_ZLIB FALSE"
		"ASSIMP_HUNTER_ENABLED FALSE"
		"ASSIMP_WARNINGS_AS_ERRORS FALSE"
	)

#stb
	CPMAddPackage(
	  NAME stb
	  GIT_TAG master
	  GITHUB_REPOSITORY nothings/stb
	  DOWNLOAD_ONLY TRUE
	)
	add_library(stb INTERFACE)
	target_include_directories(stb INTERFACE "$<BUILD_INTERFACE:${stb_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${stb_BINARY_DIR}>")


#Boost
	CPMAddPackage(
	  NAME Boost
	  VERSION 1.86.0
	  URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.tar.gz
	  OPTIONS "BOOST_ENABLE_CMAKE ON" "BOOST_INCLUDE_LIBRARIES container\\\;asio" # Note the escapes!
	)

#yaml-cpp
	CPMAddPackage(
	  NAME yaml-cpp
	  GITHUB_REPOSITORY jbeder/yaml-cpp
	  # 0.6.2 uses deprecated CMake syntax
	  VERSION 0.6.3
	  # 0.6.3 is not released yet, so use a recent commit
	  GIT_TAG 012269756149ae99745b6dafefd415843d7420bb 
	  OPTIONS
		"YAML_CPP_BUILD_TESTS Off"
		"YAML_CPP_BUILD_CONTRIB Off"
		"YAML_CPP_BUILD_TOOLS Off"
	)

#json
	CPMAddPackage(
	  NAME nlohmann_json
	  VERSION 3.7.3
	  # the git repo is incredibly large, so we download the archived include directory
	  URL https://github.com/nlohmann/json/releases/download/v3.7.3/include.zip
	  URL_HASH SHA256=87b5884741427220d3a33df1363ae0e8b898099fbc59f1c451113f6732891014
	)

	if (nlohmann_json_ADDED)
	  add_library(nlohmann_json INTERFACE IMPORTED)
	  target_include_directories(nlohmann_json INTERFACE ${nlohmann_json_SOURCE_DIR}/include)
	endif()

#FileWatch
#	CPMAddPackage(
#	  NAME FileWatch
#	  VERSION 0.0.0
#	  GIT_TAG master
#	  GITHUB_REPOSITORY ThomasMonkman/filewatch
#	)

#lua
#	CPMAddPackage(
#	  NAME lua
#	  GIT_REPOSITORY https://github.com/lua/lua.git
#	  VERSION 5.3.5
#	  DOWNLOAD_ONLY YES
#	)
#
#	if (lua_ADDED)
#	  # lua has no CMake support, so we create our own target
#
#	  FILE(GLOB lua_sources ${lua_SOURCE_DIR}/*.c)
#	  list(REMOVE_ITEM lua_sources "${lua_SOURCE_DIR}/lua.c" "${lua_SOURCE_DIR}/luac.c")
#	  add_library(lua STATIC ${lua_sources})
#
#	  target_include_directories(lua
#		PUBLIC
#		  $<BUILD_INTERFACE:${lua_SOURCE_DIR}>
#	  )
#	endif()