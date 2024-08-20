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
#-----------Platform: /-----------------------------------------------------------------------------------------------------------------------------------
			"src/Platform/Window.hpp" "src/Platform/Window.cpp" 
			"src/Platform/OpenGL/OpenGLWindow.cpp" "src/Platform/OpenGL/OpenGLWindow.hpp" 
			#"src/Platform/Vulkan/VulkanWindow.cpp" "src/Platform/Vulkan/VulkanWindow.hpp" 
#-----------Runtime: /------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Application.hpp" "src/Engine/Runtime/Application.cpp" 
			"src/Engine/Runtime/ImGui/ImGuiContext.hpp" "src/Engine/Runtime/ImGui/ImGuiContext.cpp" 
			"src/Engine/Runtime/ImGui/OpenGL/ImGuiOpenGLContext.hpp" "src/Engine/Runtime/ImGui/OpenGL/ImGuiOpenGLContext.cpp" 
			"src/Engine/Runtime/Input/InputId.hpp" 
			"src/Engine/Runtime/Input/InputContext.hpp" 
			"src/Engine/Runtime/Input/Devices/InputDevice.hpp" 
			"src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.hpp" "src/Engine/Runtime/Input/Devices/Keyboard/KeyboardDevice.cpp" 
			"src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.hpp" "src/Engine/Runtime/Input/Devices/Mouse/MouseDevice.cpp" 
			"src/Engine/Runtime/Input/InputModule.hpp" "src/Engine/Runtime/Input/InputModule.cpp" 
#-----------Systems: /------------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/Runtime/Systems/Scene/entity.hpp" "src/Engine/Runtime/Systems/Scene/entity.cpp" 
			"src/Engine/Runtime/Systems/Scene/Scene.cpp" "src/Engine/Runtime/Systems/Scene/Scene.hpp" 
			"src/Engine/Runtime/Systems/Scene/Components/MeshComponent.hpp" 
			"src/Engine/Runtime/Systems/Scene/Components/TagComponent.hpp" 
			"src/Engine/Runtime/Systems/Scene/Components/TransformComponent.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Renderer.hpp" "src/Engine/Runtime/Systems/Renderer/Renderer.cpp" 
			"src/Engine/Runtime/Systems/Renderer/RenderPass.hpp" 
			"src/Engine/Runtime/Systems/Renderer/PostProcess.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Mesh.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Model.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Material.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Image.hpp" 
			"src/Engine/Runtime/Systems/Renderer/Texture.hpp" 
			"src/Engine/Runtime/Systems/Renderer/ShaderGraph.hpp" 
#-----------RenderAPI: /----------------------------------------------------------------------------------------------------------------------------------
			"src/Engine/RenderAPI/RenderAPI.hpp"  
			"src/Engine/RenderAPI/Context.hpp" 
			"src/Engine/RenderAPI/OpenGL/OpenGLContext.hpp" "src/Engine/RenderAPI/OpenGL/OpenGLContext.cpp" 
			"src/Engine/RenderAPI/Vulkan/VulkanContext.hpp" "src/Engine/RenderAPI/Vulkan/VulkanContext.cpp" 
			"src/Engine/Core/Events/EventBus/EventBus.hpp"  "src/Engine/Core/Events/WindowEvents.hpp"

 "src/Engine/RenderAPI/OpenGL/OpenGLVertexArray.cpp" "src/Engine/RenderAPI/OpenGL/OpenGLBuffer.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Engine PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Engine PRIVATE cxx_setup glfw glad imgui ${OPENGL_LIBRARY} PUBLIC EnTT::EnTT glm::glm)
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