#include "OpenGL/OpenGLCheck.h"
#include "Log.h"

namespace Bambo
{
    void CheckOpenGLError(const std::string& filename, const std::uint_fast32_t line)
    {
        GLenum error = glGetError();
        if (error == GL_NO_ERROR) return;

        switch (error)
        {
        case GL_STACK_OVERFLOW:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "GL_STACK_OVERFLOW: This command would cause a stack overflow.");
            break;
        case GL_STACK_UNDERFLOW:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "GL_STACK_UNDERFLOW: This command would cause a stack underflow.");
            break;
        case GL_INVALID_ENUM:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "GL_INVALID_ENUM: an invalid enum value was passed to an OpenGL function");
            break;
        case GL_INVALID_VALUE:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "GL_INVALID_VALUE: an invalid value was passed to an OpenGL function");
            break;
        case GL_INVALID_OPERATION:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "GL_INVALID_OPERATION: the requested operation is not valid");
            break;
        case GL_OUT_OF_MEMORY:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s", filename.c_str(), line, "AL_OUT_OF_MEMORY: the requested operation resulted in OpenAL running out of memory");
            break;
        default:
            Logger::Get()->Log("*ERROR*", Verbosity::Fatal, "%s | %u | %s : %i", filename.c_str(), line, "UNKNOWN_ERROR", error);
        }
    }

}