cmake_minimum_required(VERSION 3.16)

option(BAMBO_DEBUG_OPTION "Enable asserts" ON)

add_subdirectory(thirdparty/GLAD)
add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/STBI)
add_subdirectory(thirdparty/GLM)
add_subdirectory(thirdparty/OpenAL)

add_subdirectory(Core)
if(BAMBO_DEBUG_OPTION)
target_compile_definitions(BamboCore PUBLIC BAMBO_DEBUG_ON)
endif()
target_compile_features(BamboCore PUBLIC cxx_std_17)

add_subdirectory(Window)
if(BAMBO_DEBUG_OPTION)
target_compile_definitions(BamboWindow PUBLIC BAMBO_DEBUG_ON)
endif()
target_compile_features(BamboWindow PUBLIC cxx_std_17)

add_subdirectory(Graphics)
if(BAMBO_DEBUG_OPTION)
target_compile_definitions(BamboGraphics PUBLIC BAMBO_DEBUG_ON)
endif()
target_compile_features(BamboGraphics PUBLIC cxx_std_17)

add_subdirectory(Audio)
if(BAMBO_DEBUG_OPTION)
target_compile_definitions(BamboAudio PUBLIC BAMBO_DEBUG_ON)
endif()
target_compile_features(BamboAudio PUBLIC cxx_std_17)



