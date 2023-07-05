#pragma once
#include "Essentials.h"
#include "Callable.h"
namespace Bambo
{
	template<typename T>
	class Delegate;

	template<typename Ret, typename... Args>
	class Delegate<Ret(Args...)>
	{
	public:
		Delegate() = default;
		Delegate(const Delegate&) = delete;
		Delegate& operator=(const Delegate&) = delete;
		Delegate(Delegate&& d) : m_callable(nullptr) { m_callable.swap(d.m_callable); }
		Delegate& operator=(Delegate&& d)
		{
			if (&d == this) return *this;
			m_callable.swap(d.m_callable);
			return *this;
		}
		~Delegate() = default;

		template<typename T>
		void Bind(T& instance, Ret(T::* ptrToFn)(Args...))
		{
			m_callable = std::make_unique<MemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
		}

		template<typename T>
		void Bind(T& instance, Ret(T::* ptrToFn)(Args...) const)
		{
			m_callable = std::make_unique<ConstMemFunCallable<T, Ret(Args...)>>(instance, ptrToFn);
		}

		bool IsValid() const { return m_callable != nullptr; }
		Ret operator()(Args... args) { return m_callable->Invoke(std::forward<Args>(args)...); }
		Ret Invoke(Args... args) { return m_callable->Invoke(std::forward<Args>(args)...); }

	private:
		UPtr<Callable<Ret(Args...)>> m_callable;
	};
}