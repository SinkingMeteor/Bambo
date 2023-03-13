#pragma once

namespace Bambo 
{
	#define BAMBO_API __declspec(dllexport)

	#ifdef BAMBO_ASSERT_ON
		#define BAMBO_ASSERT(x, msg) { if(!(x)) { fprintf(stderr, "Fatal error: %s\n", msg); __debugbreak(); }};
	#else
		#define BAMBO_ASSERT(x, msg); 
	#endif

	#define BAMBO_FALSE 0
	#define BAMBO_TRUE 1
}