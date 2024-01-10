#SpmlpeEngine
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)

if(UNIX AND NOT APPLE)
  set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
	set(CMAKE_C_COMPILER "/usr/bin/gcc-13")
endif()

SET(PROJECT_NAME SimpleEngine)
project(${PROJECT_NAME} VERSION 1.0.0)

add_subdirectory(SimpleEngineCore)
add_subdirectory(SimpleEngineEditor)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SimpleEngineEditor)
