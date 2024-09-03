add_executable(SandBox "src/Application.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SandBox PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SandBox PRIVATE cxx_setup Engine)
target_include_directories(SandBox
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )
set_target_properties(Editor PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SANDBOX_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(SANDBOX_OUTPUT_RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/res")

#target_compile_definitions(SandBox PRIVATE $<$<CONFIG:Debug>:SANDBOX_RESOURCE_DIR> $<$<CONFIG:Release>:SANDBOX_OUTPUT_RESOURCE_DIR>)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(sandbox_res ALL 
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${SANDBOX_RESOURCE_DIR}
        ${SANDBOX_OUTPUT_RESOURCE_DIR}
        COMMENT "Release mode - copying resource files"
    )
    message("Release mode - copying resource files")
    add_dependencies(SandBox sandbox_res)
else()
    message("Debug mode - not copying resource files")
endif()