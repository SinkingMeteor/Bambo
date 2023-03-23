cmake_minimum_required(VERSION 3.16)

add_subdirectory(thirdparty/GLAD)
add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/STBI)
add_subdirectory(thirdparty/GLM)

option(BAMBO_ASSERT_OPTION "Enable asserts" Off)

add_subdirectory(Core)
if(BAMBO_ASSERT_OPTION)
target_compile_definitions(BamboCore PUBLIC BAMBO_ASSERT_ON)
endif()
target_compile_features(BamboCore PUBLIC cxx_std_17)


add_subdirectory(Window)
if(BAMBO_ASSERT_OPTION)
target_compile_definitions(BamboWindow PUBLIC BAMBO_ASSERT_ON)
endif()
target_compile_features(BamboWindow PUBLIC cxx_std_17)


add_subdirectory(Graphics)
if(BAMBO_ASSERT_OPTION)
target_compile_definitions(BamboGraphics PUBLIC BAMBO_ASSERT_ON)
endif()
target_compile_features(BamboGraphics PUBLIC cxx_std_17)





