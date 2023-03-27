cmake_minimum_required(VERSION 3.16)

set(BAMBO_CORE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Time/Timer.cpp)

add_library(BamboCore STATIC ${BAMBO_CORE_SOURCES})

target_include_directories(BamboCore 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_precompile_headers(BamboCore PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)