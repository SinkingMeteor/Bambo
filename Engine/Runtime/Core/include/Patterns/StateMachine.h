#pragma once
#include "Essentials.h"

namespace Bambo
{
	class BAMBO_API IState
	{
	public:
		IState() = default;
		virtual ~IState() = default;

		virtual uint32 GetId() const = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
	};


	template<typename T>
	class BAMBO_API StateMachine final
	{
		static_assert(std::is_base_of<IState, T>::value, "Typename of statemachine is not child of IState");

	public:
		StateMachine();
		void AddState(SPtr<T> inState);
		T* GetCurrentState() { return m_currentState; }
		void EnterTo(uint32 id);
		void EnterToFirst();
		void EnterToPrevious();
		void ExitCurrentState();
		void Clear();
	private:
		std::vector<SPtr<T>> m_states;
		T* m_currentState;
		T* m_previousState;

		bool Contains(uint32 id);
		SPtr<T> Get(uint32 id);
	};

	template<typename T>
	StateMachine<T>::StateMachine() :
		m_states(),
		m_currentState(),
		m_previousState()
	{}

	template<typename T>
	void StateMachine<T>::AddState(SPtr<T> inState)
	{
		if (Contains(inState->GetId())) return;
		m_states.push_back(inState);
	}

	template<typename T>
	void StateMachine<T>::EnterTo(uint32 id)
	{
		BAMBO_ASSERT_S(Contains(id))

			m_previousState = m_currentState;
		if (m_currentState != nullptr)
		{
			m_currentState->Exit();
		}
		m_currentState = Get(id).get();
		m_currentState->Enter();
	}

	template<typename T>
	SPtr<T> StateMachine<T>::Get(uint32 id)
	{
		for (SPtr<T>& state : m_states)
		{
			if (state->GetId() == id) return state;
		}
		return nullptr;
	}

	template<typename T>
	void StateMachine<T>::EnterToFirst()
	{
		if (m_states.size() == 0) return;
		EnterTo(m_states[0]->GetId());
	}

	template<typename T>
	void StateMachine<T>::EnterToPrevious()
	{
		if (m_currentState->GetId() == m_previousState->GetId()) return;
		if (m_previousState == nullptr) return;

		if (m_currentState != nullptr)
		{
			m_currentState->Exit();
		}
		std::swap(m_currentState, m_previousState);
		m_currentState->Enter();
	}

	template<typename T>
	void StateMachine<T>::ExitCurrentState()
	{
		if (m_currentState != nullptr)
		{
			m_currentState->Exit();
		}
		m_previousState = m_currentState;
		m_currentState = nullptr;
	}

	template<typename T>
	void StateMachine<T>::Clear()
	{
		if (m_currentState != nullptr)
		{
			m_currentState->Exit();
		}

		m_currentState = nullptr;
		m_previousState = nullptr;
		m_states.clear();
	}

	template<typename T>
	bool StateMachine<T>::Contains(uint32 id)
	{
		for (SPtr<T>& state : m_states)
		{
			if (state->GetId() == id) return true;
		}
		return false;
	}
}