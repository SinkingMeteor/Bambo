cmake_minimum_required(VERSION 3.16)

set(POLYGON_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Engine.cpp)

add_executable(BamboEditor ${POLYGON_SOURCES})

target_include_directories(BamboEditor 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_compile_features(BamboEditor PUBLIC cxx_std_17)

find_package(OpenGL REQUIRED)

find_library(BAMBO_LIBS 
NAMES BamboGraphics
NAMES BamboWindow
NAMES BamboAudio
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

target_link_libraries(BamboEditor
BamboGraphics 
BamboWindow
BamboAudio
${OPENGL_LIBRARIES})

target_include_directories(BamboEditor 
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Graphics/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Audio/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Window/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/OpenAL/include/
PUBLIC ${OPENGL_INCLUDE_DIRS})
