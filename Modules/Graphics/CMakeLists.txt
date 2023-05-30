cmake_minimum_required(VERSION 3.16)

set(BAMBO_GRAPHICS_SOURCES
${CMAKE_CURRENT_LIST_DIR}/src/Shader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Texture2D.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Camera.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Renderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/SpriteRenderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLCheck.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Framebuffer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLFramebuffer.cpp
#VBO
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLVertexBufferObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/VertexBufferObject.cpp
#VAO
${CMAKE_CURRENT_LIST_DIR}/src/VertexArrayObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLVertexArrayObject.cpp
${CMAKE_CURRENT_LIST_DIR}/src/BufferLayout.cpp
#Contexts
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLGraphicsContext.cpp
${CMAKE_CURRENT_LIST_DIR}/src/GraphicsContext.cpp
#Texture
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLTexture.cpp
${CMAKE_CURRENT_LIST_DIR}/src/TextureImplementation.cpp
#Shader
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLShader.cpp
${CMAKE_CURRENT_LIST_DIR}/src/ShaderImplementation.cpp
#Renderer
${CMAKE_CURRENT_LIST_DIR}/src/RenderManager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/OpenGL/OpenGLRenderer.cpp
${CMAKE_CURRENT_LIST_DIR}/src/RendererImplementation.cpp
${CMAKE_CURRENT_LIST_DIR}/src/Transform.cpp)

add_library(BamboGraphics STATIC ${BAMBO_GRAPHICS_SOURCES})

target_include_directories(BamboGraphics 
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/
PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include/OpenGL/)

find_package(OpenGL REQUIRED)

target_include_directories(BamboGraphics 
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLFW/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLAD/include
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/STBI/
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/thirdparty/GLM/glm
PUBLIC ${BamboEngine_SOURCE_DIR}/Modules/Core/include/
PUBLIC ${BamboEngine_BINARY_DIR}/Modules/Graphics/generated/
PUBLIC ${OPENGL_INCLUDE_DIRS})

find_library(EXT_LIBS NAMES glfw glad STBI HINTS ${BamboEngine_BINARY_DIR}/Modules/thirdparty/)
target_link_libraries(BamboGraphics glfw glad STBI ${OPENGL_LIBRARIES})

find_library(BAMBO_CORE_LIB NAMES BamboCore HINTS ${BamboEngine_BINARY_DIR}/Modules/Core/)
target_link_libraries(BamboGraphics BamboCore)

set(BAMBO_GRAPHICS_RESOURCE_DIR "${BamboEngine_BINARY_DIR}/Modules/Graphics/resources")
add_definitions(-DBAMBO_GRAPHICS_RESOURCE_DIR=${BAMBO_GRAPHICS_RESOURCE_DIR})
configure_file(include/GraphicsPaths.h.in "${BamboEngine_BINARY_DIR}/Modules/Graphics/generated/GraphicsPaths.h")

add_custom_command(TARGET BamboGraphics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_LIST_DIR}/resources
    ${BamboEngine_BINARY_DIR}/Modules/Graphics/resources
    COMMENT "Copying graphics resources")