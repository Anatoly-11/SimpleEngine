#SpmlpeEngineCore
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(UNIX AND NOT APPLE)
	set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
	set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
endif()

SET(ENGINE_PROJECT_NAME SimpleEngineCore)

project(${ENGINE_PROJECT_NAME} VERSION 1.0.0)

set(ENGINE_PUBLIC_INCLUDES
	includes/SimpleEngineCore/Application.hpp
	includes/SimpleEngineCore/Log.hpp
	includes/SimpleEngineCore/Event.hpp
	includes/SimpleEngineCore/Camera.hpp
	includes/SimpleEngineCore/Keys.hpp
	includes/SimpleEngineCore/Input.hpp
)

set(ENGINE_PRIVATE_INCLUDES
	src/SimpleEngineCore/Window.hpp
	src/SimpleEngineCore/Modules/UIModule.hpp
	src/SimpleEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp
	src/SimpleEngineCore/Rendering/OpenGL/ShaderProgram.hpp
	src/SimpleEngineCore/Rendering/OpenGL/VertexBuffer.hpp
	src/SimpleEngineCore/Rendering/OpenGL/VertexArray.hpp
	src/SimpleEngineCore/Rendering/OpenGL/IndexBuffer.hpp
)

set(ENGINE_PRIVATE_SOURCES
	src/SimpleEngineCore/Application.cpp
	src/SimpleEngineCore/Window.cpp
	src/SimpleEngineCore/Modules/UIModule.cpp
	#src/SimpleEngineCore/Event.cpp
	src/SimpleEngineCore/Camera.cpp
	src/SimpleEngineCore/Input.cpp
	src/SimpleEngineCore/Rendering/OpenGL/Renderer_OpenGL.cpp
	src/SimpleEngineCore/Rendering/OpenGL/ShaderProgram.cpp
	src/SimpleEngineCore/Rendering/OpenGL/VertexBuffer.cpp
	src/SimpleEngineCore/Rendering/OpenGL/VertexArray.cpp
	src/SimpleEngineCore/Rendering/OpenGL/IndexBuffer.cpp
)

set(ENGINE_ALL_SOURCES
	${ENGINE_PUBLIC_INCLUDES}
	${ENGINE_PRIVATE_INCLUDES}
	${ENGINE_PRIVATE_SOURCES}
)

add_library(${ENGINE_PROJECT_NAME} STATIC
	${ENGINE_ALL_SOURCES}
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES
	${ENGINE_ALL_SOURCES}
)

#set(MSVC_COMPILE_DEBUG_OPTIONS "${MSVC_COMPILE_OPTIONS} /W3")
#target_compile_options(${ENGINE_PROJECT_NAME} PUBLIC "$<$<CONFIG:Debug>:${MSVC_COMPILE_DEBUG_OPTIONS}>")

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC c_std_17)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)
target_include_directories(${ENGINE_PROJECT_NAME} PRIVATE src)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)

add_subdirectory(../external/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE spdlog)

add_subdirectory(../external/glad ${CMAKE_CURRENT_BINARY_DIR}/glad)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glad)

add_subdirectory(../external/glm ${CMAKE_CURRENT_BINARY_DIR}/glm)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glm)

set(IMGUI_INCLUDES
	../external/imgui/imgui.h
	../external/imgui/backends/imgui_impl_opengl3.h
	../external/imgui/backends/imgui_impl_glfw.h
	
)

set(IMGUI_SOURCES
	../external/imgui/imgui.cpp
	../external/imgui/backends/imgui_impl_opengl3.cpp
	../external/imgui/backends/imgui_impl_glfw.cpp
	../external/imgui/imgui_demo.cpp
	../external/imgui/imgui_tables.cpp
	../external/imgui/imgui_widgets.cpp
	../external/imgui/imgui_draw.cpp	
)

add_library(ImGui STATIC
	${IMGUI_INCLUDES}
	${IMGUI_SOURCES}
)

target_include_directories(ImGui PUBLIC ../external)
target_include_directories(ImGui PUBLIC ../external/imgui)
target_link_libraries(ImGui PRIVATE glad glfw)

target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE ImGui)
