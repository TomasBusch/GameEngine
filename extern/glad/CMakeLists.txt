cmake_minimum_required(VERSION 3.21)

project(glad)

add_library(glad STATIC)
target_sources(glad PRIVATE "src/gl.c" "src/vulkan.c")
target_include_directories(glad PUBLIC "include")