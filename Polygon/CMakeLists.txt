cmake_minimum_required(VERSION 3.16)

set(POLYGON_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Main.cpp)

add_executable(Polygon ${POLYGON_SOURCES})

target_include_directories(Polygon 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_compile_features(Polygon PUBLIC cxx_std_17)

find_library(BAMBO_LIB 
NAMES Bambo
HINTS ${CMAKE_BINARY_DIR}/Engine/)

target_link_libraries(Polygon Bambo)

target_include_directories(Polygon 
PUBLIC ${PROJECT_SOURCE_DIR}/Engine/include/)

add_custom_command(TARGET Polygon POST_BUILD
COMMAND ${CMAKE_COMMAND} -E copy
${CMAKE_BINARY_DIR}/Engine/Bambo.dll
${CMAKE_CURRENT_BINARY_DIR}/Bambo.dll
COMMENT "Copying dll")