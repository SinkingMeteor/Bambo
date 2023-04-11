cmake_minimum_required(VERSION 3.16)

set(BAMBO_GRAPHICS_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Audio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioDevice.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioSource.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioListener.cpp
${CMAKE_CURRENT_LIST_DIR}/src/ALCheck.cpp)

add_library(BamboAudio STATIC ${BAMBO_GRAPHICS_SOURCES})

target_include_directories(BamboAudio 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/OpenAL/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/)

find_library(BamboCore NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Engine/Core)
find_library(BAMBO_OPENAL_LIB NAMES OpenAL32 HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/OpenAL REQUIRED)

target_link_libraries(BamboAudio PUBLIC BamboCore PUBLIC OpenAL32)

