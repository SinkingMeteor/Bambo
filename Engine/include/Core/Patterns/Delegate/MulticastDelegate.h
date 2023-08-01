#pragma once
#include "Essentials.h"
#include "Callable.h"
#include "Delegate.h"

namespace Bambo
{
    template <typename T>
    class MulticastDelegate;
    template <typename T>
    class Delegate;
    template <typename T>
    class Callable;

    class Connection
    {
    public:
        template <typename Ret, typename... Args>
        Connection(MulticastDelegate<Ret(Args...)>* delegate, Callable<Ret(Args...)>* callable) :
            m_delegate(delegate),
            m_callable(callable),
            m_disconnectFunction(&DisconnectFunction<Ret, Args...>) {}
        void Disconnect() { m_disconnectFunction(m_delegate, m_callable); }
    private:
        void (*m_disconnectFunction)(void*, void*);
        void* m_delegate;
        void* m_callable;

        template <typename Ret, typename... Args>
        static void DisconnectFunction(void* delegate, void* callable)
        {
            static_cast<MulticastDelegate<Ret(Args...)>*>(delegate)->Unbind(static_cast<Callable<Ret(Args...)>*>(callable));
        }
    };

	template<typename Ret, typename... Args>
	class MulticastDelegate<Ret(Args...)>
	{
        friend Connection;

        template<typename T>
        using FnPtr = Ret(T::*)(Args...);

        template<typename T>
        using ConstFnPtr = Ret(T::*)(Args...) const;

    public:
        MulticastDelegate() = default;

        template<typename T>
        Connection Bind(T& instance, FnPtr<T> fnPtr)
        {
            Delegate<Ret(Args...)> delegate{};
            m_delegates.push_back(std::move(delegate));
            m_delegates.back().Bind(instance, fnPtr);
            return Connection(this, m_delegates.back().m_callable.get());
        }

        template<typename T>
        Connection Bind(T& instance, ConstFnPtr<T> fnPtr)
        {
            Delegate<Ret(Args...)> delegate{};
            m_delegates.push_back(std::move(delegate));
            m_delegates.back().Bind(instance, fnPtr);
            return Connection(this, m_delegates.back().m_callable.get());
        }

        void operator()(Args... args)
        {
            for (Delegate<Ret(Args...)>& delegate : m_delegates)
            {
                delegate.Invoke(std::forward<Args>(args)...);
            }
        }

        void Invoke(Args... args)
        {
            for (Delegate<Ret(Args...)>& delegate : m_delegates)
            {
                delegate.Invoke(std::forward<Args>(args)...);
            }
        }

        bool IsValid() const { return !m_delegates.empty(); }

    private:
        using Delegate_t = Delegate<Ret(Args...)>;

        std::vector<Delegate_t> m_delegates;

        void Unbind(Callable<Ret(Args...)>* callable)
        {
            auto end = m_delegates.end();
            for (auto it = m_delegates.begin(); it != end; ++it)
            {
                if (it->m_callable.get() == callable)
                {
                    m_delegates.erase(it);
                    return;
                }
            }
        }
	};
}