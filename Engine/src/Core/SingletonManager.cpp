#include "Core/SingletonManager.h"

namespace Bambo
{
	SingletonManager* SingletonManager::Get()
	{
		static SingletonManager instance;
		return &instance;
	}
}