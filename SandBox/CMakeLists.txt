add_executable(SandBox "src/Application.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SandBox PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(SandBox PRIVATE Engine cxx_setup)
target_include_directories(SandBox
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )