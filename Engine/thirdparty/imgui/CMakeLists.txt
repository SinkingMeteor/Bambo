cmake_minimum_required(VERSION 3.16)

set(IMGUI_SOURCES 
${CMAKE_CURRENT_LIST_DIR}/src/imgui.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_draw.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_impl_glfw.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_impl_opengl3.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_tables.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_demo.cpp
${CMAKE_CURRENT_LIST_DIR}/src/imgui_widgets.cpp)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLFW/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/misc/)

