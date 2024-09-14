add_library(imgui INTERFACE)
target_include_directories(imgui INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
target_sources(imgui INTERFACE 
				"imgui/backends/imgui_impl_glfw.cpp" 
				"imgui/backends/imgui_impl_opengl3.cpp"
				"imgui/backends/imgui_impl_sdl3.cpp"
				"imgui/imgui.cpp"
				"imgui/imgui_demo.cpp"
				"imgui/imgui_draw.cpp"
				"imgui/imgui_tables.cpp"
				"imgui/imgui_widgets.cpp"
				"imgui/misc/cpp/imgui_stdlib.cpp"
				"imgui/misc/fonts/binary_to_compressed_c.cpp"
)
#target_link_libraries(imgui PRIVATE glfw ${OPENGL_LIBRARY})
add_library(imgui_header INTERFACE)
target_include_directories(imgui_header INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/imgui")


