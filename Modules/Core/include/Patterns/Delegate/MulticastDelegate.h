#pragma once
#include "Essentials.h"

namespace Bambo
{
	template<typename T>
	class MulticastDelegate;

	template<typename Ret, typename... Args>
	class MulticastDelegate<Ret(Args...)>
	{

	};
}