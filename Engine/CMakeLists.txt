add_library (Engine STATIC
#-----------General Header files--------------------------------------------------------------------------------------------------------------------------
			"src/Engine.h" 
			"src/pch.h" "src/pch.cpp" 
#-----------Core: /---------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Core/Base.h" 
			"src/Engine/Core/Utils/ENGINE_API.h" 
			"src/Engine/Core/Utils/Callback.h" 
			"src/Engine/Core/Time/Timer.h" "src/Engine/Core/Time/Timer.cpp" 
			"src/Engine/Core/Time/Timestep.h" 
			"src/Engine/Core/Time/Timestamp.h" 
			"src/Engine/Core/Debug/Assert.h" 
			"src/Engine/Core/Memory/SmartPointers.h" 
			"src/Engine/Core/Events/Event.h" 
			"src/Engine/Core/Events/EventQueue.h" 
			"src/Engine/Core/Events/Publisher.h" "src/Engine/Core/Events/Subscriber.h" 
			"src/Engine/Core/Events/InputEvents.h" 
#-----------Platform: /-----------------------------------------------------------------------------------------------------------------------------------
			"src/Platform/Window.h" "src/Platform/Window.cpp" 
			"src/Platform/OpenGL/OpenGLWindow.cpp" "src/Platform/OpenGL/OpenGLWindow.h" 
			#"src/Platform/Vulkan/VulkanWindow.cpp" "src/Platform/Vulkan/VulkanWindow.h" 
#-----------Runtime: /------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Application.h" "src/Engine/Runtime/Application.cpp" 
			"src/Engine/Runtime/ImGui/ImGuiContext.h" "src/Engine/Runtime/ImGui/ImGuiContext.cpp" 
			"src/Engine/Runtime/ImGui/OpenGL/ImGuiOpenGLContext.h" "src/Engine/Runtime/ImGui/OpenGL/ImGuiOpenGLContext.cpp" 
			"src/Engine/Runtime/Input/Input.h" 
			"src/Engine/Runtime/Input/InputId.h" 
			"src/Engine/Runtime/Input/InputContext.h" 
			"src/Engine/Runtime/Input/Devices/InputDevice.h" 
			"src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.h" "src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.cpp" 
			"src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.h" "src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.cpp" 
			"src/Engine/Runtime/Input/InputHandler.h" "src/Engine/Runtime/Input/InputHandler.cpp" 
#-----------Systems: /------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Systems/Scene/entity.h" "src/Engine/Runtime/Systems/Scene/entity.cpp" 
			"src/Engine/Runtime/Systems/Scene/Scene.cpp" "src/Engine/Runtime/Systems/Scene/Scene.h" 
			"src/Engine/Runtime/Systems/Scene/Components/MeshComponent.h" 
			"src/Engine/Runtime/Systems/Scene/Components/TagComponent.h" 
			"src/Engine/Runtime/Systems/Scene/Components/TransformComponent.h" 
			"src/Engine/Runtime/Systems/Renderer/Renderer.h" "src/Engine/Runtime/Systems/Renderer/Renderer.cpp" 
			"src/Engine/Runtime/Systems/Renderer/RenderPass.h" 
			"src/Engine/Runtime/Systems/Renderer/PostProcess.h" 
			"src/Engine/Runtime/Systems/Renderer/Mesh.h" 
			"src/Engine/Runtime/Systems/Renderer/Model.h" 
			"src/Engine/Runtime/Systems/Renderer/Material.h" 
			"src/Engine/Runtime/Systems/Renderer/Image.h" 
			"src/Engine/Runtime/Systems/Renderer/Texture.h" 
			"src/Engine/Runtime/Systems/Renderer/ShaderGraph.h" 
#-----------RenderAPI: /----------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/RenderAPI/RenderAPI.h" 
			"src/Engine/RenderAPI/Context.h" 
			"src/Engine/RenderAPI/OpenGL/OpenGLContext.h" "src/Engine/RenderAPI/OpenGL/OpenGLContext.cpp" 
			"src/Engine/RenderAPI/Vulkan/VulkanContext.h" "src/Engine/RenderAPI/Vulkan/VulkanContext.cpp" 
  "src/Engine/Core/Events/EventBus/EventBus.h" "src/Engine/Core/Events/EventBus/EventBusTest.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Engine PRIVATE cxx_setup glfw glad glm::glm imgui ${OPENGL_LIBRARY} PUBLIC EnTT::EnTT)
target_include_directories(Engine 
						   PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src" 
						   #PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/include"
						  )

target_precompile_headers(Engine PRIVATE "src/pch.h")

if(MSVC) # If using the VS compiler...
	target_compile_definitions(Engine PUBLIC _CRT_SECURE_NO_WARNINGS)

	set_target_properties(Engine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup") #no console
endif()

target_compile_definitions(Engine PUBLIC GLFW_INCLUDE_NONE)