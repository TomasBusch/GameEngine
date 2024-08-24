add_executable(Editor "src/Application.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Editor PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Editor PRIVATE Engine cxx_setup)
target_include_directories(Editor
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )
set_target_properties(Editor PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")

set(EDITOR_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(EDITOR_OUTPUT_RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/res")

add_custom_command(
    TARGET Editor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${EDITOR_RESOURCE_DIR}
        ${EDITOR_OUTPUT_RESOURCE_DIR}
    COMMENT "Copying resources to build directory"
)