#gladxt
cmake_minimum_required(VERSION 3.24 FATAL_ERROR)


project(glad)

add_library(glad STATIC
 include/glad/glad.h
 src/glad.c
)

target_include_directories(glad PUBLIC include/)

#target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_features(${ENGINE_PROJECT_NAME} PUBLIC c_std_17)
