cmake_minimum_required(VERSION 3.16)

set(BAMBO_CORE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Log.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Utils.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Time/Timer.cpp)

add_library(BamboCore STATIC ${BAMBO_CORE_SOURCES})

target_include_directories(BamboCore 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${CMAKE_BINARY_DIR}/generated/)


set(BAMBO_RESOURCE_DIR "${PROJECT_SOURCE_DIR}/Engine/resources")
add_definitions(-DBAMBO_PROJECT_DIR="${PROJECT_SOURCE_DIR}")
add_definitions(-DBAMBO_RESOURCE_DIR=${BAMBO_RESOURCE_DIR})
configure_file(include/Paths.h.in "${CMAKE_BINARY_DIR}/generated/Paths.h")

target_precompile_headers(BamboCore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)