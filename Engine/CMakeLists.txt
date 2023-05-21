cmake_minimum_required(VERSION 3.16)

add_subdirectory(thirdparty/flecs)
add_subdirectory(thirdparty/imgui)

set(BAMBO_ENGINE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Main/Main.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Main/Engine.cpp
${CMAKE_CURRENT_LIST_DIR}/src/World/World.cpp
${CMAKE_CURRENT_LIST_DIR}/src/GUI/GUIWorld.cpp
${CMAKE_CURRENT_LIST_DIR}/src/World/Entity.cpp)

add_executable(Bambo ${BAMBO_ENGINE_SOURCES} "include/Main/Module.h")

target_include_directories(Bambo
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/World/Components)

target_compile_features(Bambo PUBLIC cxx_std_17)

find_library(BAMBO_ENGINE_LIBS 
NAMES BamboGraphics BamboWindow BamboAudio
HINTS ${BamboEngine_BINARY_DIR}/Modules/)

find_library(THIRDPARTY_LIBS
NAMES flecs imgui
HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/)

target_link_libraries(Bambo
BamboGraphics 
BamboWindow
BamboAudio
imgui
flecs_static)

target_include_directories(Bambo 
PUBLIC ${BamboEngine_BINARY_DIR}/Engine/generated/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/flecs/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/imgui/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Core/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Graphics/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Audio/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Window/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/OpenAL/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/
PUBLIC ${OPENGL_INCLUDE_DIRS})

set(BAMBO_ENGINE_RESOURCE_DIR "${BamboEngine_SOURCE_DIR}/Engine/resources")
add_definitions(-DBAMBO_ENGINE_RESOURCE_DIR=${BAMBO_ENGINE_RESOURCE_DIR})
configure_file(include/BamboPaths.h.in "${BamboEngine_BINARY_DIR}/Engine/generated/BamboPaths.h")

target_precompile_headers(Bambo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/engpch.h)