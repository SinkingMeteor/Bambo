#pragma once
#include "Essentials.h"

namespace Bambo
{
	template<typename T>
	class Callable;

	template<typename Ret, typename... Args>
	class Callable<Ret(Args...)>
	{
	public:
		virtual ~Callable() = default;
		virtual Ret Invoke(Args... args) = 0;
	protected:
		Callable() = default;
	};

	template<typename Ret, typename T>
	class MemFunCallable;

	template<typename T, typename Ret, typename... Args>
	class MemFunCallable<T, Ret(Args...)> final : public Callable<Ret(Args...)>
	{
		using PtrToFn = Ret(T::*)(Args...);
	public:
		MemFunCallable(T& instance, PtrToFn ptrToFunction) : m_instance(instance), m_ptrToFunction(ptrToFunction) {}
		virtual Ret Invoke(Args... args) override { return (m_instance.*m_ptrToFunction)(std::forward<Args>(args)...); }
	private:
		T& m_instance;
		PtrToFn m_ptrToFunction;
	};

	template<typename Ret, typename T>
	class ConstMemFunCallable;

	template<typename T, typename Ret, typename... Args>
	class ConstMemFunCallable<T, Ret(Args...)> final : public Callable<Ret(Args...)>
	{
		using ConstPtrToFn = Ret(T::*)(Args...) const;
	public:
		ConstMemFunCallable(T& instance, ConstPtrToFn ptrToFunctionConst) : m_instance(instance), m_ptrToFunctionConst(ptrToFunctionConst) {}
		virtual Ret Invoke(Args... args) override { return (m_instance.*m_ptrToFunctionConst)(std::forward<Args>(args)...); }
	private:
		T& m_instance;
		ConstPtrToFn m_ptrToFunctionConst;
	};
}