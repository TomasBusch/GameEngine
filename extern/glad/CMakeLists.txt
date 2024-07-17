cmake_minimum_required(VERSION 3.21)

project(glad)

add_library(glad)
target_sources(glad PRIVATE "src/gl.c" "src/vulkan.c")
target_include_directories(glad INTERFACE include)