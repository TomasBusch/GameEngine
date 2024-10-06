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

if(NOT CMAKE_MAXIMUM_RECURSION_DEPTH)
  set(CMAKE_MAXIMUM_RECURSION_DEPTH 4000)
endif()

project (
	"GameEngine"
	VERSION 0.0.1.0
	DESCRIPTION ""
	LANGUAGES CXX C
)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

#Set this to compile dll files to the same directory as the executable since RPATH is not supported on Windows
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}")

include(cmake/CPM.cmake)
set(CPM_SOURCE_CACHE "${CMAKE_CURRENT_LIST_DIR}/packages")
set(CPM_USE_LOCAL_PACKAGES TRUE)
CPMUsePackageLock(package-lock.cmake)

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
#find_package(Git QUIET)
#
#if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
#    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
#                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#                    RESULT_VARIABLE GIT_SUBMODULE_RESULT)
#    if(NOT GIT_SUBMODULE_RESULT EQUAL "0")
#        message(FATAL_ERROR "git submodule update --init --recursive failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
#    endif()
#endif()

#TODO Execute utils/git-sync-deps with python to complete the shaderc install

# Include sub-projects.
add_subdirectory("Engine")
add_subdirectory("Editor")
add_subdirectory("SandBox")



