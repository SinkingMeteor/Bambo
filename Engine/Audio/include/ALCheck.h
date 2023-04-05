#pragma once
#include "pch.h"
#include "AL/al.h"
#include "Utils.h"
namespace Bambo
{
#ifdef BAMBO_DEBUG_ON

#define ALCheck(expr)                                      \
    do                                                     \
    {                                                      \
        expr;                                              \
        CheckALError(__FILE__, __LINE__);                   \
    } while (false)

#else

#define ALCheck(expr)  (expr)

#endif

    void CheckALError(const std::string& filename, const std::uint_fast32_t line);

}