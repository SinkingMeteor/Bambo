cmake_minimum_required(VERSION 3.16)

set(BAMBO_ENGINE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Engine.cpp)

add_executable(Bambo ${BAMBO_ENGINE_SOURCES})

target_include_directories(Bambo
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_compile_features(Bambo PUBLIC cxx_std_17)

find_library(BAMBO_ENGINE_LIBS 
NAMES BamboGraphics
NAMES BamboWindow
NAMES BamboAudio
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

target_link_libraries(Bambo
BamboGraphics 
BamboWindow
BamboAudio)

target_include_directories(Bambo 
PUBLIC ${BamboEngine_BINARY_DIR}/Bambo/generated/
PUBLIC ${BamboEngine_SOURCE_DIR}/Bambo/thirdparty/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Graphics/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Audio/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Window/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/OpenAL/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PUBLIC ${OPENGL_INCLUDE_DIRS})

set(BAMBO_ENGINE_RESOURCE_DIR "${BamboEngine_SOURCE_DIR}/Bambo/resources")
add_definitions(-DBAMBO_ENGINE_RESOURCE_DIR=${BAMBO_ENGINE_RESOURCE_DIR})
configure_file(include/BamboPaths.h.in "${BamboEngine_BINARY_DIR}/Bambo/generated/BamboPaths.h")

target_precompile_headers(Bambo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/engpch.h)