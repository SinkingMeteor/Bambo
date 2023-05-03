#pragma once
#include "pch.h"
#include "Graphics.h"
namespace Bambo
{
#ifdef BAMBO_DEBUG_ON

#define OpenGLCheck(expr)                                      \
    do                                                     \
    {                                                      \
        expr;                                              \
        CheckOpenGLError(__FILE__, __LINE__);                   \
    } while (false)

#else

#define OpenGLCheck(expr)  (expr)

#endif

    void CheckOpenGLError(const std::string& filename, const std::uint_fast32_t line);
}