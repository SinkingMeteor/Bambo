cmake_minimum_required(VERSION 3.16)

set(BAMBO_EDITOR_SOURCES
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/SceneHierarchy.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/GameViewport.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/ContentBrowser.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/EditorModule.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Project.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Main.cpp)

add_executable(BamboEditor ${BAMBO_EDITOR_SOURCES})

target_include_directories(BamboEditor 
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PUBLIC ${BamboEngine_SOURCE_DIR}/Editor/include/
PUBLIC ${BamboEngine_BINARY_DIR}/Editor/generated/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Core/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Window/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Graphics/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Audio/include/)

find_library(BAMBO_ENGINE_LIB
NAMES Bambo
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

set(BAMBO_EDITOR_CONFIG_DIR "${BamboEngine_BINARY_DIR}/Editor/")
add_definitions(-DBAMBO_EDITOR_CONFIG_DIR=${BAMBO_EDITOR_CONFIG_DIR})
configure_file(include/EditorPaths.h.in "${BamboEngine_BINARY_DIR}/Editor/generated/EditorPaths.h")

set(BAMBO_EDITOR_RESOURCE_DIR "${BamboEngine_BINARY_DIR}/Editor/")
add_definitions(-DBAMBO_EDITOR_RESOURCE_DIR=${BAMBO_EDITOR_RESOURCE_DIR})
configure_file(include/EditorPaths.h.in "${BamboEngine_BINARY_DIR}/Editor/generated/EditorPaths.h")

target_link_libraries(BamboEditor Bambo)

add_custom_command(TARGET BamboEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/resources
    ${BamboEngine_BINARY_DIR}/Editor/resources
    COMMENT "Copying graphics resources")