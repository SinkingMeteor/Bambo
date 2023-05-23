cmake_minimum_required(VERSION 3.16)

set(BAMBO_POLYGON_SOURCES
${BamboEngine_SOURCE_DIR}/Polygon/src/Main.cpp)

add_executable(BamboPolygon ${BAMBO_POLYGON_SOURCES})

target_include_directories(BamboPolygon 
PUBLIC ${BamboEngine_SOURCE_DIR}/Polygon/include/
PUBLIC ${BamboEngine_SOURCE_DIR}/Engine/include/)

find_library(BAMBO_ENGINE_LIB
NAMES Bambo
HINTS ${BamboEngine_BINARY_DIR}/Engine/)

target_link_libraries(BamboPolygon Bambo)

