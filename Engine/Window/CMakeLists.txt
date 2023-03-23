cmake_minimum_required(VERSION 3.16)

set(BAMBO_WINDOW_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Window.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Input.cpp)

add_library(BamboWindow STATIC ${BAMBO_WINDOW_SOURCES})

target_include_directories(BamboWindow
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

find_package(OpenGL REQUIRED)

target_include_directories(BamboWindow
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLFW/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLAD/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/
PUBLIC ${OPENGL_INCLUDE_DIRS})

find_library(EXT_LIBS NAMES glfw glad STBI HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/)
target_link_libraries(BamboWindow glfw glad STBI ${OPENGL_LIBRARIES})

find_library(BAMBO_CORE_LIB NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Engine/Core/)
target_link_libraries(BamboWindow BamboCore)


