#pragma once

namespace Bambo
{
	template<typename T>
	class Singleton
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