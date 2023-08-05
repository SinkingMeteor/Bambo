cmake_minimum_required(VERSION 3.16)

add_subdirectory(thirdparty/GLAD)
add_subdirectory(thirdparty/GLFW)
add_subdirectory(thirdparty/STBI)
add_subdirectory(thirdparty/GLM)
add_subdirectory(thirdparty/OpenAL)

set(BAMBO_ENGINE_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Audio/Audio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioDevice.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioSource.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioListener.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioWavLoader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/StreamingAudio.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/Sound.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/Music.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioUtils.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/AudioManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Audio/ALCheck.cpp

${CMAKE_CURRENT_LIST_DIR}/src/Core/Engine.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Core/TimeManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Core/Log.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Core/Utils.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Core/SingletonManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Core/Time/Timer.cpp
##======Graphics======
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Shader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Texture2D.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Camera.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Renderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/SpriteRenderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLCheck.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Framebuffer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLFramebuffer.cpp
#VBO
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLVertexBufferObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/VertexBufferObject.cpp
#VAO
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/VertexArrayObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLVertexArrayObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/BufferLayout.cpp
#Contexts
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLGraphicsContext.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/GraphicsContext.cpp
#Texture
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLTexture.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/TextureImplementation.cpp
#Shader
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLShader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/ShaderImplementation.cpp
#Renderer
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/RenderManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/OpenGL/OpenGLRenderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/RendererImplementation.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Graphics/Transform.cpp
##======End Graphics======

${CMAKE_CURRENT_LIST_DIR}/src/Window/WindowsWindow.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Window/WindowManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Window/Window.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Window/Input.cpp

${CMAKE_CURRENT_LIST_DIR}/src/World/World.cpp
${CMAKE_CURRENT_LIST_DIR}/src/World/Components/ComponentFactory.cpp

#${CMAKE_CURRENT_LIST_DIR}/src/Serialization/WorldSerialization.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Serialization/MathSerialization.cpp)

add_library(BamboEngine STATIC ${BAMBO_ENGINE_SOURCES})

target_include_directories(BamboEngine
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${BamboEngine_BINARY_DIR}/Engine/generated/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLFW/include/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/OpenAL/include/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLM/glm
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/GLAD/include
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/thirdparty/STBI/
PUBLIC ${OPENGL_INCLUDE_DIRS})

target_compile_features(BamboEngine PUBLIC cxx_std_17)

find_library(THIRDPARTY_LIBS NAMES glfw glad OpenAL STBI ${OPENGL_LIBRARIES} HINTS ${BamboEngine_BINARY_DIR}/Engine/thirdparty/)

target_link_libraries(BamboEngine
PUBLIC glfw 
PUBLIC glad 
PUBLIC STBI 
PUBLIC OpenAL)

set(BAMBO_ENGINE_RESOURCE_DIR "${BamboEngine_SOURCE_DIR}/Engine/resources")
add_definitions(-DBAMBO_ENGINE_RESOURCE_DIR=${BAMBO_ENGINE_RESOURCE_DIR})

configure_file(include/BamboPaths.h.in "${BamboEngine_BINARY_DIR}/Engine/generated/BamboPaths.h")

target_precompile_headers(BamboEngine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/pch.h)
