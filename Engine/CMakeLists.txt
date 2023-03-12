cmake_minimum_required(VERSION 3.16)
project(BamboEngine)

set(BAMBO_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Bambo.cpp)

add_library(Bambo SHARED ${BAMBO_SOURCES})

target_include_directories(Bambo 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/)

target_compile_features(Bambo PUBLIC cxx_std_17)
target_precompile_headers(Bambo PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)
