# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")



project (
	"VulkanGameEngine"
	VERSION 0.0.1.0
	DESCRIPTION ""
	LANGUAGES CXX
)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build using shared libraries" FORCE)
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

#Set /cmake folder as the modules path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

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

#include external projects
add_subdirectory("extern/assimp")
add_subdirectory("extern/entt")
add_subdirectory("extern/filewatch")
add_subdirectory("extern/glad")
add_subdirectory("extern/glfw")
add_subdirectory("extern/glm")
add_subdirectory("extern/imgui")
add_subdirectory("extern/SDL")
add_subdirectory("extern/spdlog")
#add_subdirectory("extern/stb")
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE "${PROJECT_SOURCE_DIR}/extern/stb")
add_subdirectory("extern/yaml-cpp")

find_package(OpenGL REQUIRED)

# Include sub-projects.
add_subdirectory("Engine")
add_subdirectory("Editor")
add_subdirectory("SandBox")


