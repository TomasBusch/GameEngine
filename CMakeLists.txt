# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.25)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set(VS_STARTUP_PROJECT Editor)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project (
	"VulkanGameEngine"
	VERSION 0.0.1.0
	DESCRIPTION ""
	LANGUAGES CXX
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build using shared libraries" FORCE)

set(SHADERC_SKIP_TESTS ON CACHE BOOL "Enable test for shaderc" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(GLM_BUILD_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(GLSLANG_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SDL_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SHADERC_ENABLE_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SPDLOG_BUILD_TESTS_HO OFF CACHE BOOL "Enable test" FORCE)
set(SPIRV_CROSS_ENABLE_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SPIRV_HEADERS_ENABLE_TESTS OFF CACHE BOOL "Enable test" FORCE)
set(SPIRV_SKIP_TESTS ON CACHE BOOL "Enable test" FORCE)
set(gmock_build_tests OFF CACHE BOOL "Enable test" FORCE)
set(gtest_build_tests OFF CACHE BOOL "Enable test" FORCE)


set(SPIRV_CROSS_STATIC ON CACHE BOOL "Build SPIRV-Cross as static" FORCE)
set(SPIRV_CROSS_SKIP_INSTALL ON CACHE BOOL "Skip SPIRV-Cross Installation" FORCE)
set(SPIRV_CROSS_ENABLE_CPP ON CACHE BOOL "Build cpp module of SPIRV-Cross" FORCE)
set(SPIRV_CROSS_ENABLE_GLSL ON CACHE BOOL "Build GLSL module of SPIRV-Cross" FORCE)
set(SPIRV_CROSS_ENABLE_MSL ON CACHE BOOL "Build MSL module of SPIRV-Cross" FORCE)
set(SPIRV_CROSS_ENABLE_HLSL ON CACHE BOOL "Build HLSL module of SPIRV-Cross" FORCE)
set(SPIRV_CROSS_ENABLE_REFLECT ON CACHE BOOL "Build reflect module of SPIRV-Cross" FORCE)
set(SPIRV_CROSS_ENABLE_UTIL ON CACHE BOOL "Build util module of SPIRV-Cross" FORCE)

#set(ENTT_INCLUDE_HEADERS OFF CACHE BOOL "Include EnTT Headers" FORCE)

#Setup compiler config
add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup
    INTERFACE -Wall)
target_compile_features(cxx_setup 
    INTERFACE cxx_std_20)
target_include_directories(cxx_setup
    INTERFACE "${PROJECT_SOURCE_DIR}/include")

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  target_compile_definitions(cxx_setup INTERFACE COMPILER_CLANG)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_definitions(cxx_setup INTERFACE COMPILER_GNU)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
  target_compile_definitions(cxx_setup INTERFACE COMPILER_INTEL)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
  target_compile_definitions(cxx_setup INTERFACE COMPILER_MSVC)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  target_compile_definitions(cxx_setup INTERFACE LINUX)
  message(STATUS "Configuring on/for Linux")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  target_compile_definitions(cxx_setup INTERFACE MAC_OS)
    message(STATUS "Configuring on/for MacOS")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  target_compile_definitions(cxx_setup INTERFACE WIN_32)
      message(STATUS "Configuring on/for Windows")
elseif(CMAKE_SYSTEM_NAME STREQUAL "AIX")
  message(FATAL_ERROR "IBM AIX Not supported")
else()
  message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} Not supported")
endif() 

if(MSVC)
    target_compile_options(cxx_setup 
        INTERFACE
            /EHsc
            /W2
            # /Wall
    )
else()

    target_compile_options(cxx_setup 
        INTERFACE
            -Wall
            # -Wextra
            # -Wpedantic
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(cxx_setup INTERFACE DEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
  target_compile_definitions(cxx_setup INTERFACE RELEASE)
endif()

#Set /cmake folder as the modules path
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#Setup generation of global project variables in c++
configure_file("config.hpp.in" "${PROJECT_SOURCE_DIR}/include/config.hpp" ESCAPE_QUOTES)

#Auto-pull submodules
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMODULE_RESULT)
    if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

#TODO Execute utils/git-sync-deps with python to complete the shaderc install


#include external projects
add_subdirectory("extern/assimp")
set_target_properties(assimp uninstall PROPERTIES FOLDER extern)
add_subdirectory("extern/entt")
set_target_properties(EnTT PROPERTIES FOLDER extern)
add_subdirectory("extern/filewatch")
set_target_properties(filewatch_unit PROPERTIES FOLDER extern)
add_subdirectory("extern/glad")
set_target_properties(glad PROPERTIES FOLDER extern)
add_subdirectory("extern/glfw")
set_target_properties(glfw PROPERTIES FOLDER extern)
add_subdirectory("extern/glm")
set_target_properties(glm glm-header-only PROPERTIES FOLDER extern)
add_subdirectory("extern/imgui")
set_target_properties(imgui imgui_header PROPERTIES FOLDER extern)
add_subdirectory("extern/SDL")
set_target_properties(SDL3_test SDL3-static PROPERTIES FOLDER extern)
add_subdirectory("extern/spdlog")
set_target_properties(spdlog PROPERTIES FOLDER extern)
#add_subdirectory("extern/stb")
add_subdirectory("extern/shaderc")
set_target_properties(testdata shaderc shaderc-online-compile shaderc_shared shaderc_util add-copyright check-copyright build-version glslc glslc_exe shaderc_combined shaderc_combined-pkg-config shaderc_static-pkg-config shaderc-pkg-config PROPERTIES FOLDER extern)
add_subdirectory("extern/SPIRV-Cross")
set_target_properties(spirv-cross spirv-cross-c spirv-cross-core spirv-cross-cpp spirv-cross-glsl spirv-cross-hlsl spirv-cross-msl spirv-cross-reflect spirv-cross-util core_tables enum_string_mapping extinst_tables spirv-tools-pkg-config PROPERTIES FOLDER extern)
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "${PROJECT_SOURCE_DIR}/extern/stb")
add_subdirectory("extern/yaml-cpp")
set_target_properties(yaml-cpp yaml-cpp-parse yaml-cpp-read yaml-cpp-sandbox PROPERTIES FOLDER extern)

set_target_properties(zlibstatic PROPERTIES FOLDER extern)

find_package(OpenGL REQUIRED)

#Select Vulkan Components
set(VULKAN_COMPONENTS
	"glslc"
	"glslangValidator"
	"glslang"
	"shaderc_combined"
	"SPIRV-Tools"
	"dxc"
)

#Find Vulkan
find_package(Vulkan REQUIRED COMPONENTS "${VULKAN_COMPONENTS}")
if(NOT Vulkan_FOUND)
	message(FATAL_ERROR "Vulkan SDK could not be found, make sure that the SDK is installed!")
else()
	message(STATUS "Vulkan: Version ${Vulkan_VERSION}")
endif()

# Include sub-projects.
add_subdirectory("Engine")
add_subdirectory("Editor")
add_subdirectory("SandBox")


