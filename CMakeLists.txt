# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.21)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (
	"VulkanGameEngine"
	VERSION 0.0.1.0
	DESCRIPTION ""
	LANGUAGES CXX
)

#Setup compiler config
add_library(cxx_setup INTERFACE)
target_compile_options(cxx_setup
  INTERFACE -Wall)
target_compile_features(cxx_setup INTERFACE cxx_std_20)
target_include_directories(cxx_setup
  INTERFACE "${PROJECT_SOURCE_DIR}/include")

#Set /cmake folder as the modules path
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#Setup generation of global project variables in c++
configure_file("config.h.in" "${PROJECT_SOURCE_DIR}/include/config.h" ESCAPE_QUOTES)

#Auto-pull submodules
find_package(Git QUIET)

if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
    endif()
endif()

# Include sub-projects.
add_subdirectory("Engine")
add_subdirectory("Editor")
add_subdirectory("SandBox")
