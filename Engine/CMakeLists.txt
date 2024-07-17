add_library (Engine "src/Engine.cpp" "src/Engine.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Engine PRIVATE cxx_setup glfw)
target_include_directories(Engine
                           INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           )
if(MSVC) # If using the VS compiler...
	target_compile_definitions(Engine PUBLIC _CRT_SECURE_NO_WARNINGS)

	set_target_properties(Engine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
endif()