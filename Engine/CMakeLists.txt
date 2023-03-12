cmake_minimum_required(VERSION 3.16)
project(BamboEngine)

set(BAMBO_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Bambo.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Window/Window.cpp)

add_library(Bambo SHARED ${BAMBO_SOURCES})

target_include_directories(Bambo 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/GLAD)

target_include_directories(Bambo 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLFW/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLAD/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLM/glm)

find_library(GLFW_LIB NAMES glfw glad HINTS ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/)
target_link_libraries(Bambo glfw glad)

target_compile_features(Bambo PUBLIC cxx_std_17)
target_precompile_headers(Bambo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)
