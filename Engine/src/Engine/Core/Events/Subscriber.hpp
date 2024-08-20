#pragma once

#include "Engine/Core/Base.hpp"
#include "Engine/Core/Events/EventQueue.hpp"

namespace Engine {

	template<typename T>
	class Publisher;

	template<typename T>
	class Subscriber {
	public:
		Subscriber() = delete;
		Subscriber(Callback<T> cb) 
			:m_Callback(cb)
		{}
		~Subscriber() = default;

		int Next() { 
			if (!m_EventQueue.Empty()) {
				m_Callback(m_EventQueue.Pop());
				return 1;
			}
			else {
				return 0;
			}
		}
	private:
		void Update(T e) { m_EventQueue.Push(e); }
	private:
		uint64_t m_Handle;
		Callback<T> m_Callback;
		EventQueue<T> m_EventQueue;

		friend Publisher<T>;
	};
}