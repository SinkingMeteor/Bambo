#pragma once
#include "pch.h"

namespace Bambo
{
	template<typename T>
	class BAMBO_API Singleton
	{
	public:
		Singleton(const Singleton& singleton) = delete;
		Singleton& operator=(const Singleton& singleton) = delete;
		
		static T* Get() 
		{
			static T instance;
			return &instance;
		}
	protected:
		Singleton() = default;
	};
}