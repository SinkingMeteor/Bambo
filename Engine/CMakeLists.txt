cmake_minimum_required(VERSION 3.16)

option(BAMBO_DEBUG_OPTION "Enable asserts" ON)

add_subdirectory(thirdparty/GLAD)
add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/STBI)
add_subdirectory(thirdparty/GLM)
add_subdirectory(thirdparty/OpenAL)

macro(ConfigureLib LibName SubDirectory)
	add_subdirectory(${SubDirectory})
	if(BAMBO_DEBUG_OPTION)
		target_compile_definitions(${LibName} PUBLIC BAMBO_DEBUG_ON)
	endif()
	target_compile_features(${LibName} PUBLIC cxx_std_17)
endmacro()

ConfigureLib(BamboCore Core)
ConfigureLib(BamboWindow Window)
ConfigureLib(BamboGraphics Graphics)
ConfigureLib(BamboAudio Audio)
