cmake_minimum_required(VERSION 3.16)

set(BAMBO_GRAPHICS_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Audio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioDevice.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioSource.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioListener.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioWavLoader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/StreamingAudio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Sound.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Music.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioUtils.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/ALCheck.cpp)

add_library(BamboAudio STATIC ${BAMBO_GRAPHICS_SOURCES} "include/AudioUtils.h")

target_include_directories(BamboAudio 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/OpenAL/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Core/include/)

find_library(BamboCore NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Modules/Core)
find_library(OPENAL_LIBRARY NAMES OpenAL HINTS ${BamboEngine_BINARY_DIR}/Modules/thirdparty/OpenAL)

target_link_libraries(BamboAudio PUBLIC BamboCore OpenAL)

