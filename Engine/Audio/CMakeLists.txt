cmake_minimum_required(VERSION 3.16)

set(BAMBO_GRAPHICS_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Audio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/AudioDevice.cpp
${CMAKE_CURRENT_LIST_DIR}/src/ALCheck.cpp)

add_library(BamboAudio STATIC ${BAMBO_GRAPHICS_SOURCES})

target_include_directories(BamboAudio 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_include_directories(BamboAudio 
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/openal-soft/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/)

find_library(EXT_LIBS NAMES OpenAL32 HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/)
target_link_libraries(BamboAudio OpenAL32 ${OPENGL_LIBRARIES})

find_library(BAMBO_CORE_LIB NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Engine/Core/)
target_link_libraries(BamboAudio BamboCore)

