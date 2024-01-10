#SpmlpeEngineCore
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
	set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
endif()

SET(ENGINE_PROJECT_NAME SimpleEngineCore)

project(${ENGINE_PROJECT_NAME} VERSION 1.0.0)

add_library(${ENGINE_PROJECT_NAME} STATIC
	src/SimpleEngineCore/Utils/test.cpp
	includes/SimpleEngineCore/Utils/test.hpp
)

target_include_directories(${ENGINE_PROJECT_NAME} PUBLIC includes)

target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC c_std_17)

add_subdirectory(../external/glfw ${CMAKE_CURRENT_BINARY_DIR}/glfw)
target_link_libraries(${ENGINE_PROJECT_NAME} PRIVATE glfw)