add_library (Engine STATIC
#-----------General.hppeader files--------------------------------------------------------------------------------------------------------------------------
			"src/Engine.hpp" 
			"src/pch.hpp" "src/pch.cpp" 
#-----------Core: /---------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Core/Base.hpp" 
			"src/Engine/Core/Utils/ENGINE_API.hpp" 
			"src/Engine/Core/Utils/Callback.hpp" 
			"src/Engine/Core/Time/Timer.hpp" "src/Engine/Core/Time/Timer.cpp" 
			"src/Engine/Core/Time/Timestep.hpp" 
			"src/Engine/Core/Time/Timestamp.hpp" 
			"src/Engine/Core/Debug/Assert.hpp" 
			"src/Engine/Core/Memory/SmartPointers.hpp" 
			"src/Engine/Core/Events/Event.hpp" 
			"src/Engine/Core/Events/EventQueue.hpp" 
			"src/Engine/Core/Events/Publisher.hpp" "src/Engine/Core/Events/Subscriber.hpp" 
			"src/Engine/Core/Events/InputEvents.hpp" 
			"src/Engine/Core/Events/WindowEvents.hpp" 
			"src/Engine/Core/Events/EventBus/EventBus.hpp" 
#-----------Platform: /-----------------------------------------------------------------------------------------------------------------------------------
			"src/Platform/Window.hpp" "src/Platform/Window.cpp" 
			"src/Platform/OpenGL/GLFWOpenGLWindow.cpp" "src/Platform/OpenGL/GLFWOpenGLWindow.hpp" 
			"src/Platform/OpenGL/SDL3OpenGLWindow.cpp" "src/Platform/OpenGL/SDL3OpenGLWindow.hpp"
			#"src/Platform/Vulkan/VulkanWindow.cpp" "src/Platform/Vulkan/VulkanWindow.hpp" 
#-----------Runtime: /------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Application.hpp" "src/Engine/Runtime/Application.cpp" 
			"src/Engine/Runtime/ImGui/ImGuiContext.hpp" "src/Engine/Runtime/ImGui/ImGuiContext.cpp" 
			"src/Engine/Runtime/ImGui/GLFW/ImGuiGLFWContext.hpp" "src/Engine/Runtime/ImGui/GLFW/ImGuiGLFWContext.cpp" 
			"src/Engine/Runtime/ImGui/SDL3/ImGuiSDL3Context.hpp" "src/Engine/Runtime/ImGui/SDL3/ImGuiSDL3Context.cpp" 
			"src/Engine/Runtime/Input/InputId.hpp" 
			"src/Engine/Runtime/Input/InputContext.hpp" 
			"src/Engine/Runtime/Input/Devices/InputDevice.hpp" 
			"src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.hpp" "src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.cpp" 
			"src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.hpp" "src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.cpp" 
			"src/Engine/Runtime/Input/InputModule.hpp" "src/Engine/Runtime/Input/InputModule.cpp" 
			"src/Engine/Runtime/Resources/ShaderModule.cpp" 
#-----------Scene: /--------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Scene/entity.hpp" "src/Engine/Runtime/Scene/entity.cpp" 
			"src/Engine/Runtime/Scene/Scene.cpp" "src/Engine/Runtime/Scene/Scene.hpp" 
			"src/Engine/Runtime/Scene/Components/MeshComponent.hpp" 
			"src/Engine/Runtime/Scene/Components/TagComponent.hpp" 
			"src/Engine/Runtime/Scene/Components/TransformComponent.hpp" 
#-----------Renderer: /-----------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Renderer/Renderer.hpp" "src/Engine/Runtime/Renderer/Renderer.cpp" 
			"src/Engine/Runtime/Renderer/RenderPass.hpp" 
			"src/Engine/Runtime/Renderer/PostProcess.hpp" 
			"src/Engine/Runtime/Renderer/Mesh.hpp" 
			"src/Engine/Runtime/Renderer/Model.hpp" 
			"src/Engine/Runtime/Renderer/Material.hpp" 
			"src/Engine/Runtime/Renderer/Image.hpp" 
			"src/Engine/Runtime/Renderer/Texture.hpp" 
			"src/Engine/Runtime/Renderer/ShaderGraph.hpp" 
#-----------RenderAPI: /----------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/RenderAPI/RenderAPI.hpp"  
			"src/Engine/RenderAPI/Context.hpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLContext.hpp" "src/Engine/RenderAPI/OpenGL/OpenGLContext.cpp" 
			"src/Engine/RenderAPI/Vulkan/VulkanContext.hpp" "src/Engine/RenderAPI/Vulkan/VulkanContext.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLVertexArray.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLBuffer.cpp" 
			"src/Engine/Core/Debug/Logger.cpp"  
			"src/Engine/RenderAPI/OpenGL/OpenGLIndexBuffer.cpp" 
			"src/Engine/RenderAPI/Context.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLFramebuffer.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLTexture.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLUniformBuffer.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLShaderStorageBuffer.cpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLPixelBuffer.cpp"
			"src/Platform/SDL3/SDL3Input.cpp"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Engine 
				PRIVATE cxx_setup imgui glfw SDL3-static glad shaderc spirv-cross-c spirv-cross-cpp Vulkan::dxc_lib ${OPENGL_LIBRARY} 
				PUBLIC EnTT::EnTT glm::glm imgui_header spdlog
)
target_include_directories(Engine 
						   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" 
						   #PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
						  )

target_precompile_headers(Engine PRIVATE "src/pch.hpp")

if(MSVC) # If using .hppe VS compiler...
	target_compile_definitions(Engine PUBLIC _CRT_SECURE_NO_WARNINGS)

	set_target_properties(Engine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
endif()

target_compile_definitions(Engine PUBLIC GLFW_INCLUDE_NONE)

set(ENGINE_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(ENGINE_OUTPUT_RESOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/res")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(engine_res ALL 
        COMMAND ${CMAKE_COMMAND} -E copy_directory 
        ${ENGINE_RESOURCE_DIR}
        ${ENGINE_OUTPUT_RESOURCE_DIR}
        COMMENT "Release mode - copying resource files"
    )
    message("Release mode - copying resource files")
    add_dependencies(Engine engine_res)
else()
    message("Debug mode - not copying resource files")
endif()