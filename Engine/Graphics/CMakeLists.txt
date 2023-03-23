cmake_minimum_required(VERSION 3.16)

set(BAMBO_GRAPHICS_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Shader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Texture2D.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Sprite.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Camera.cpp
${CMAKE_CURRENT_LIST_DIR}/src/RenderTarget.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Transform.cpp)

add_library(BamboGraphics STATIC ${BAMBO_GRAPHICS_SOURCES})

target_include_directories(BamboGraphics 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

find_package(OpenGL REQUIRED)

target_include_directories(BamboGraphics 
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLFW/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLAD/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/STBI/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/
PUBLIC ${OPENGL_INCLUDE_DIRS})

find_library(EXT_LIBS NAMES glfw glad STBI HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/)
target_link_libraries(BamboGraphics glfw glad STBI ${OPENGL_LIBRARIES})

find_library(BAMBO_CORE_LIB NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Engine/Core/)
target_link_libraries(BamboGraphics BamboCore)

