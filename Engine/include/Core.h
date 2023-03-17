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

	using uint = unsigned int;
	using uchar = unsigned char;
	using bambo_id = std::size_t;

	constexpr float ONE_DEGREE_IN_RADIANS = 0.0174532f;
	constexpr float ONE_RADIAN_IN_DEGREES = 57.2957795f;
}