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