#pragma once
#include<memory>

constexpr const bool BAMBO_FALSE = 0;
constexpr const bool BAMBO_TRUE = 1;

using int32 = std::int32_t;
using uint64 = std::uint64_t;
using uint32 = std::uint32_t;
using uint16 = std::uint16_t;
using uint8 = std::uint8_t;
using bambo_id = std::size_t;

template<typename T>
using UPtr = std::unique_ptr<T>;
template<typename T>
using SPtr = std::shared_ptr<T>;
template<typename T>
using WPtr = std::weak_ptr<T>;

#define BAMBO_API __declspec(dllexport)

#ifdef BAMBO_EDITOR_ON
	#define WITH_EDITOR
#endif

#ifdef BAMBO_DEBUG_ON

	namespace Bambo
	{
		namespace Internal
		{
			template<typename Cond>
			inline void InternalAssert(Cond cond, const char* pr) { if (!(cond)) { fprintf(stderr, "Fatal error: %s\n", pr); __debugbreak(); } }
			template<typename Cond>
			inline void InternalAssert(Cond cond) { if (!(cond)) { __debugbreak(); } }
		}
	}

	#define BAMBO_ASSERT(x, msg) Bambo::Internal::InternalAssert(x, msg);
	#define BAMBO_ASSERT_S(x) Bambo::Internal::InternalAssert(x);
	#define BAMBO_NOT_IMPLEMENTED() BAMBO_ASSERT(false, "Not implemented function reached.");
#else
	#define BAMBO_ASSERT(x, msg); 
	#define BAMBO_ASSERT_S(x); 
	#define BAMBO_NOT_IMPLEMENTED();
#endif

#ifdef _WIN32
	#ifdef _WIN64
		#define BAMBO_CURRENT_OS_WINDOWS
	#else
		#error "Unsupported windows system"
	#endif
#else
	#error "Unsupported platform"
#endif

#define DECLARE_LOG_CATEGORY_STATIC(logCategory) static const char* logCategory = #logCategory;
#define DECLARE_LOG_CATEGORY_EXTERN(logCategory) extern const char* logCategory = #logCategory;

namespace Bambo
{
	template<typename To, typename From>
	To* Cast(From* fromType)
	{
		if (fromType == nullptr) return nullptr;
		return static_cast<To*>(fromType);
	}
}