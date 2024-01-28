#SpmlpeEngineEditor
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(UNIX AND NOT APPLE)
	set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
	set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
endif()

SET(EDITOR_PROJECT_NAME SimpleEngineEditor)

project(${EDITOR_PROJECT_NAME} VERSION 1.0.0)

add_executable(${EDITOR_PROJECT_NAME}
	src/main.cpp
)

target_link_libraries(${EDITOR_PROJECT_NAME} SimpleEngineCore ImGui glm)

target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_features(${EDITOR_PROJECT_NAME} PUBLIC c_std_17)

set_target_properties(${EDITOR_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
