cmake_minimum_required(VERSION 3.16)

set(BAMBO_EDITOR_CORE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Engine.cpp)

add_executable(BamboEditorCore ${BAMBO_EDITOR_CORE_SOURCES})

target_include_directories(BamboEditorCore 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_compile_features(BamboEditorCore PUBLIC cxx_std_17)

find_library(BAMBO_ENGINE_LIBS 
NAMES BamboGraphics
NAMES BamboWindow
NAMES BamboAudio
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

find_library(THIRDPARTY_LIBS
NAMES imgui
HINTS ${BamboEngine_BINARY_DIR}/Editor/thirdparty/)

target_link_libraries(BamboEditorCore
BamboGraphics 
BamboWindow
BamboAudio
imgui)

target_include_directories(BamboEditorCore 
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Core/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Graphics/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Audio/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/Window/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/OpenAL/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Editor/thirdparty/imgui/include/
PUBLIC ${OPENGL_INCLUDE_DIRS})
