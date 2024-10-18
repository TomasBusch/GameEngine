#pragma once

#include "Subscriber.hpp"
#include "Engine/Core/Base.hpp"

namespace Engine {
	template<typename T>
	class Publisher {
	public:
		Publisher() = default;
		~Publisher() = default;

		Subscriber<T>* Subscribe(Callback<T> cb) {
			Subscriber<T>* sub = new Subscriber<T>(cb);
			m_Subscribers.push_back(sub);
			return sub;
		}
		void Publish(T e) {
			for (Subscriber<T>* sub : m_Subscribers) {
				sub->Update(e);
			}
		}
	private:
		std::vector< Subscriber<T>* > m_Subscribers;
	};
}