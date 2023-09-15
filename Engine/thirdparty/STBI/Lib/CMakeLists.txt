cmake_minimum_required(VERSION 3.16)
project(stbi_image)

add_library(STBI ${CMAKE_CURRENT_LIST_DIR}/stb_image.cpp)
target_include_directories(STBI PUBLIC ${CMAKE_CURRENT_LIST_DIR}/)