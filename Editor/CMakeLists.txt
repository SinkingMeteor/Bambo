cmake_minimum_required(VERSION 3.16)

add_subdirectory(thirdparty/rttr)

set(BAMBO_EDITOR_SOURCES
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/SceneHierarchy.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/GameViewport.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/ContentBrowser.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Windows/ProjectBrowser.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/EditorStates/OpenProjectEditorState.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/EditorStates/MainEditorState.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/EditorModule.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Project.cpp
${BamboEngine_SOURCE_DIR}/Editor/src/Main.cpp)

add_executable(BamboEditor ${BAMBO_EDITOR_SOURCES} )

target_include_directories(BamboEditor 
PRIVATE ${BamboEngine_SOURCE_DIR}/Engine/include/
PRIVATE ${BamboEngine_SOURCE_DIR}/Engine/thirdparty/
PRIVATE ${BamboEngine_SOURCE_DIR}/Editor/thirdparty/
PRIVATE ${BamboEngine_SOURCE_DIR}/Editor/include/
PRIVATE ${BamboEngine_BINARY_DIR}/Editor/generated/
PRIVATE ${BamboEngine_SOURCE_DIR}/Modules/Core/include/
PRIVATE ${BamboEngine_SOURCE_DIR}/Modules/Window/include/
PRIVATE ${BamboEngine_SOURCE_DIR}/Modules/Graphics/include/
PRIVATE ${BamboEngine_SOURCE_DIR}/Modules/Audio/include/)

target_include_directories(BamboEditor
PRIVATE ${BamboEngine_SOURCE_DIR}/Editor/thirdparty/rttr/src/)

find_library(BAMBO_ENGINE_LIB
NAMES Bambo
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

find_library(THIRDPARTY_LIBS
NAMES RTTR::Core
HINTS ${BamboEngine_BINARY_DIR}/Editor/thirdparty/)

set(BAMBO_EDITOR_CONFIG_DIR "${BamboEngine_BINARY_DIR}/Editor/")
set(BAMBO_EDITOR_RESOURCE_DIR "${BamboEngine_BINARY_DIR}/Editor/")
add_definitions(-DBAMBO_EDITOR_CONFIG_DIR=${BAMBO_EDITOR_CONFIG_DIR})
add_definitions(-DBAMBO_EDITOR_RESOURCE_DIR=${BAMBO_EDITOR_RESOURCE_DIR})
configure_file(include/EditorPaths.h.in "${BamboEngine_BINARY_DIR}/Editor/generated/EditorPaths.h")
configure_file(include/EditorConfig.json.in "${BamboEngine_BINARY_DIR}/Editor/EditorConfig.json")

target_link_libraries(BamboEditor Bambo rttr_core)

add_custom_command(TARGET BamboEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/resources
    ${BamboEngine_BINARY_DIR}/Editor/resources
    COMMENT "Copying graphics resources")

add_custom_command(TARGET BamboEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${BamboEngine_BINARY_DIR}/Editor/thirdparty/rttr/bin/rttr_core_d.dll
    ${BamboEngine_BINARY_DIR}/Editor/)