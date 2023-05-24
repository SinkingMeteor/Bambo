cmake_minimum_required(VERSION 3.16)

set(BAMBO_EDITOR_SOURCES
${BamboEngine_SOURCE_DIR}/Editor/src/EditorModule.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Main.cpp)

add_executable(BamboEditor ${BAMBO_EDITOR_SOURCES})

target_include_directories(BamboEditor 
PUBLIC ${BamboEngine_SOURCE_DIR}/Editor/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/include/)

find_library(BAMBO_ENGINE_LIB
NAMES Bambo
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

target_link_libraries(BamboEditor Bambo)

