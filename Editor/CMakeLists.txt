file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(Editor "src/Application.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Editor PROPERTY CXX_STANDARD 20)
endif()


target_link_libraries(Editor PRIVATE Engine cxx_setup)
target_include_directories(Editor
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )