cmake_minimum_required(VERSION 3.16)

add_subdirectory(thirdparty/imgui)

set(BAMBO_EDITOR_SOURCES
${Bambo_SOURCE_DIR}/Editor/src/Windows/SceneHierarchy.cpp
${Bambo_SOURCE_DIR}/Editor/src/Windows/GameViewport.cpp
${Bambo_SOURCE_DIR}/Editor/src/Windows/Inspector.cpp
${Bambo_SOURCE_DIR}/Editor/src/Windows/ContentBrowser.cpp
${Bambo_SOURCE_DIR}/Editor/src/Windows/ProjectBrowser.cpp

${Bambo_SOURCE_DIR}/Editor/src/Drawers/InspectorDrawersRegistry.cpp
${Bambo_SOURCE_DIR}/Editor/src/Drawers/PrimitiveDrawers.cpp
${Bambo_SOURCE_DIR}/Editor/src/Drawers/DefaultDrawers.cpp

${Bambo_SOURCE_DIR}/Editor/src/EditorStates/OpenProjectEditorState.cpp
${Bambo_SOURCE_DIR}/Editor/src/EditorStates/MainEditorState.cpp
${Bambo_SOURCE_DIR}/Editor/src/Widget/FileBrowserWidget.cpp
${Bambo_SOURCE_DIR}/Editor/src/EditorModule.cpp
${Bambo_SOURCE_DIR}/Editor/src/Project.cpp
${Bambo_SOURCE_DIR}/Editor/src/GUIWorld.cpp
${Bambo_SOURCE_DIR}/Editor/src/Main.cpp)

add_executable(BamboEditor ${BAMBO_EDITOR_SOURCES})

target_include_directories(BamboEditor 
PRIVATE ${CMAKE_CURRENT_LIST_DIR}/thirdparty/imgui/include/
PRIVATE ${Bambo_SOURCE_DIR}/Editor/include/
PRIVATE ${Bambo_BINARY_DIR}/Editor/generated/)

find_library(BAMBO_ENGINE_LIB NAMES BamboEngine HINTS ${Bambo_BINARY_DIR}/Engine/)
find_library(THIRDPARTY_LIB NAMES imgui HINTS ${Bambo_BINARY_DIR}/Editor/)

set(BAMBO_EDITOR_CONFIG_DIR "${Bambo_BINARY_DIR}/Editor/")
set(BAMBO_EDITOR_RESOURCE_DIR "${Bambo_BINARY_DIR}/Editor/")

add_definitions(-DBAMBO_EDITOR_CONFIG_DIR=${BAMBO_EDITOR_CONFIG_DIR})
add_definitions(-DBAMBO_EDITOR_RESOURCE_DIR=${BAMBO_EDITOR_RESOURCE_DIR})

configure_file(include/EditorPaths.h.in "${Bambo_BINARY_DIR}/Editor/generated/EditorPaths.h")
configure_file(include/EditorConfig.json.in "${Bambo_BINARY_DIR}/Editor/EditorConfig.json")

target_compile_definitions(BamboEditor PUBLIC BAMBO_EDITOR_ON)

target_link_libraries(BamboEditor 
PRIVATE BamboEngine 
PRIVATE imgui)

add_custom_command(TARGET BamboEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/resources
    ${Bambo_BINARY_DIR}/Editor/resources
    COMMENT "Copying graphics resources")
