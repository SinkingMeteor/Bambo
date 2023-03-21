cmake_minimum_required(VERSION 3.16)
project(BamboEngine)

set(BAMBO_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Engine.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Window/Window.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Input/Input.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Shader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Texture2D.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Sprite.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Camera.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/RenderTarget.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Common/Transform.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Common/Resource/ResourceProvider.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Common/Time/Timer.cpp)

add_library(Bambo SHARED ${BAMBO_SOURCES})

target_include_directories(Bambo 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/GLAD)
add_subdirectory(thirdparty/STBI)
find_package(OpenGL REQUIRED)

target_compile_definitions(Bambo PUBLIC BAMBO_ASSERT_ON)

target_include_directories(Bambo 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLFW/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLAD/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/STBI/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLM/glm)

find_library(GLFW_LIB NAMES glfw glad STBI OpenGL HINTS ${CMAKE_CURRENT_BINARY_DIR}/thirdparty/)
target_link_libraries(Bambo glfw glad STBI)

target_compile_features(Bambo PUBLIC cxx_std_17)
target_precompile_headers(Bambo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)

add_custom_command(TARGET Bambo POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy_directory
${CMAKE_CURRENT_LIST_DIR}/resources
${CMAKE_BINARY_DIR}/Engine/resources
COMMENT "Copying resources")
