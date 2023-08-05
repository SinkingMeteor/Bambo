#pragma once
#include "pch.h"

namespace Bambo
{
	class ISingleton
	{
	public:
		virtual ~ISingleton() = default;
	protected:
		ISingleton() = default;
	};

	class BAMBO_API SingletonManager final
	{
	public:
		SingletonManager(const SingletonManager& singleton) = delete;
		SingletonManager& operator=(const SingletonManager& singleton) = delete;
		
		template<typename T, typename ...Args>
		T* Register(Args&&... args)
		{
			std::size_t typeID = T::SingletonID();

			auto it = m_objects.find(typeID);
			if (it != m_objects.end()) return nullptr;
		
			m_objects[typeID] = std::make_unique<T>(std::forward<Args>(args)...);
			return GetSingleton<T>();
		}

		template<typename T>
		T* GetSingleton()
		{
			std::size_t typeID = T::SingletonID();

			auto it = m_objects.find(typeID);
			if (it == m_objects.end()) return nullptr;

			return static_cast<T*>(it->second.get());
		}

		static SingletonManager* Get();
	protected:
		SingletonManager() = default;
	private:
		std::unordered_map<std::size_t, UPtr<ISingleton>> m_objects;
	};

#define SINGLETON_BODY(T, N) public: \
		static std::size_t SingletonID() { return N; } \
		static T* Get() { return SingletonManager::Get()->GetSingleton<T>(); } 
}