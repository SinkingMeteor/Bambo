#pragma once

namespace Bambo 
{
	constexpr const bool BAMBO_FALSE = 0;
	constexpr const bool BAMBO_TRUE = 1;

	using uint = unsigned int;
	using uchar = unsigned char;
	using bambo_id = size_t;
}

	#define BAMBO_API __declspec(dllexport)

	#ifdef BAMBO_DEBUG_ON
		#define BAMBO_ASSERT(x, msg) { if(!(x)) { fprintf(stderr, "Fatal error: %s\n", msg); __debugbreak(); }};
	#else
		#define BAMBO_ASSERT(x, msg); 
	#endif