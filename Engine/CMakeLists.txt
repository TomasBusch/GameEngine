add_library (Engine STATIC 
			"src/include/Engine.h" 
			"src/pch.h" "src/pch.cpp" 
			"src/Core/Application.cpp" "src/Core/Application.h" "src/Core/Definitions/BuildDLL.h" "src/Core/Definitions/Memory.h" "src/Core/Layers/Layer.h" "src/Core/Time/Timer.h" "src/Core/Time/Timer.cpp" "src/Core/Time/Timestep.h"  "src/Core/Layers/DebugUILayer.h" 
			"src/Platform/Window.h" "src/Platform/MultiPlatform/MultiPlatformWindow.cpp" "src/Platform/MultiPlatform/MultiPlatformWindow.h" "src/Platform/Window.cpp" "src/Platform/OpenGL/OpenGLWindow.cpp" "src/Platform/OpenGL/OpenGLWindow.h" "src/Platform/Vulkan/VulkanWindow.cpp" "src/Platform/Vulkan/VulkanWindow.h"  
			"src/RenderAPI/Context.h" "src/RenderAPI/OpenGL/OpenGLContext.h" "src/RenderAPI/OpenGL/OpenGLContext.cpp" "src/RenderAPI/Vulkan/VulkanContext.cpp" "src/RenderAPI/Vulkan/VulkanContext.h" 
			"src/Systems/Renderer/Renderer.h" "src/Systems/Renderer/Renderer.cpp" "src/Systems/Renderer/RenderPass.h" "src/Systems/Renderer/PostProcess.h" "src/Systems/Renderer/Mesh.h" "src/Systems/Renderer/Model.h" "src/Systems/Renderer/Material.h" "src/Systems/Renderer/Image.h" "src/Systems/Renderer/Texture.h" "src/Systems/Renderer/ShaderGraph.h"
			"src/Systems/Scene/Scene.h" "src/Systems/Scene/Scene.cpp" "src/Systems/Scene/Entity.h" "src/Systems/Scene/Entity.cpp" 
			"src/Systems/Scene/Components/TagComponent.h" "src/Systems/Scene/Components/TransformComponent.h" "src/Systems/Scene/Components/MeshComponent.h" "src/Systems/Scene/Components/DynamicMeshComponent.h" "src/Systems/ResourceManager/ModelManager.h" 
			"src/GUI/ImguiContext.h" "src/GUI/ImguiOpenGLContext.h" "src/GUI/ImguiOpenGLContext.cpp" 
)

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