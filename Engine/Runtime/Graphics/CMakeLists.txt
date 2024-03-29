cmake_minimum_required(VERSION 3.16)

set(MODULE_NAME GRAPHICS)
set(CURRENT_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})

set(BAMBO_${MODULE_NAME}_SOURCES

${CURRENT_MODULE_DIR}/src/Font.cpp
${CURRENT_MODULE_DIR}/src/Text.cpp
${CURRENT_MODULE_DIR}/src/Shader.cpp
${CURRENT_MODULE_DIR}/src/Texture2D.cpp
${CURRENT_MODULE_DIR}/src/TextureBuffer.cpp
${CURRENT_MODULE_DIR}/src/Camera.cpp
${CURRENT_MODULE_DIR}/src/Sprite.cpp
${CURRENT_MODULE_DIR}/src/SpriteRenderer.cpp
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLCheck.cpp
${CURRENT_MODULE_DIR}/src/DrawDebugHelpers.cpp
${CURRENT_MODULE_DIR}/src/DebugLineRenderer.cpp
${CURRENT_MODULE_DIR}/src/Framebuffer.cpp
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLFramebuffer.cpp
#VBO
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLVertexBufferObject.cpp
${CURRENT_MODULE_DIR}/src/VertexBufferObject.cpp
#VAO
${CURRENT_MODULE_DIR}/src/VertexArrayObject.cpp
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLVertexArrayObject.cpp
${CURRENT_MODULE_DIR}/src/BufferLayout.cpp
#IBO
${CURRENT_MODULE_DIR}/src/IndexBufferObject.cpp
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLIndexBufferObject.cpp
#Contexts
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLGraphicsContext.cpp
${CURRENT_MODULE_DIR}/src/GraphicsContext.cpp
#Texture
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLTexture.cpp
${CURRENT_MODULE_DIR}/src/TextureImplementation.cpp
#Shader
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLShader.cpp
${CURRENT_MODULE_DIR}/src/ShaderImplementation.cpp
#Renderer
${CURRENT_MODULE_DIR}/src/RenderManager.cpp
${CURRENT_MODULE_DIR}/src/OpenGL/OpenGLRenderer.cpp
${CURRENT_MODULE_DIR}/src/RendererImplementation.cpp
${CURRENT_MODULE_DIR}/src/Transform.cpp)

set(BAMBO_${MODULE_NAME}_PUBLIC_LIBS glfw glad ${OPENGL_LIBRARIES})
set(BAMBO_${MODULE_NAME}_PRIVATE_LIBS STBI freetype)
set(BAMBO_${MODULE_NAME}_PUBLIC_PATHS ${CURRENT_MODULE_DIR}/include/)
set(BAMBO_${MODULE_NAME}_PRIVATE_PATHS)

set(MODULE_SOURCES ${BAMBO_${MODULE_NAME}_SOURCES} PARENT_SCOPE)
set(MODULE_PUBLIC_LIBS ${BAMBO_${MODULE_NAME}_PUBLIC_LIBS} PARENT_SCOPE)
set(MODULE_PRIVATE_LIBS ${BAMBO_${MODULE_NAME}_PRIVATE_LIBS} PARENT_SCOPE)
set(MODULE_PUBLIC_PATHS ${BAMBO_${MODULE_NAME}_PUBLIC_PATHS} PARENT_SCOPE)
set(MODULE_PRIVATE_PATHS ${BAMBO_${MODULE_NAME}_PRIVATE_PATHS} PARENT_SCOPE)