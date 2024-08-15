#pragma once
#include "pch.h"
#include "Engine/Core/Base.h"


namespace Engine {
	template<typename Interface>
	class EventBus {
	public:

		class Handler : public Interface {
		public:
			void BusConnect();
			void BusDisconnect();
		private:
			friend EventBus;
		};

	public:
		static bool HasHandlers();

		template<typename Function, typename... ArgsT>
		static void Broadcast(Function&& func, ArgsT&&... args);

		template<typename Function, typename... ArgsT>
		static void QueueBroadcast(Function&& func, ArgsT&&... args);

		static void ExecuteQueue();
	private:
		static void Connect(Handler* handler);
		static void Disconnect(Handler* handler);
		static EventBus& Get() {
			if (g_Instance == nullptr) {
				g_Instance = new EventBus();
			}
			return *g_Instance;
		}
	private:
		std::vector<Handler*> m_Handlers{};
		std::queue<Callback<Handler*>> m_Queue{};

	public: inline static EventBus* g_Instance = nullptr;
	};

	template<typename Interface>
	inline bool EventBus<Interface>::HasHandlers()
	{
		return false;
	}

	template<typename Interface>
	template<typename Function, typename ...ArgsT>
	inline void EventBus<Interface>::Broadcast(Function&& func, ArgsT && ...args)
	{
		EventBus<Interface> instance = EventBus::Get();
		for (Handler* handler : instance.m_Handlers) {
			(handler->*func)(std::forward<ArgsT>(args)...);
		}
	}

	template<typename Interface>
	template<typename Function, typename ...ArgsT>
	inline void EventBus<Interface>::QueueBroadcast(Function&& func, ArgsT && ...args)
	{
		EventBus<Interface> instance = EventBus::Get();
		instance.m_Queue.push([func = std::forward<Function>(func), args...](Handler* handler) {
				(handler->*func)(std::forward<ArgsT>(args)...);
			}
		);
	}

	template<typename Interface>
	inline void EventBus<Interface>::ExecuteQueue()
	{
		EventBus<Interface> instance = EventBus::Get();
		while (!instance.m_Queue.empty()) {
			Callback<Handler*> callback = instance.m_Queue.front();
			for (Handler* handler : instance.m_Handlers) {
				callback(handler);
			}
			instance.m_Queue.pop();
		}
	}

	template<typename Interface>
	inline void EventBus<Interface>::Connect(Handler* handler)
	{
		auto pos = std::find(EventBus::Get().m_Handlers.begin(), EventBus::Get().m_Handlers.end(), handler);
		if (pos == EventBus::Get().m_Handlers.end()) {
			EventBus::Get().m_Handlers.push_back(handler);
		}
		int a = 1;
	}

	template<typename Interface>
	inline void EventBus<Interface>::Disconnect(Handler* handler)
	{
		EventBus<Interface> instance = EventBus::Get();
		auto pos = std::find(instance.m_Handlers.begin(), instance.m_Handlers.end(), handler);
		if (pos != instance.m_Handlers.end()) {
			instance.m_Handlers.erase(pos);
		}
	}

	template<typename Interface>
	inline void EventBus<Interface>::Handler::BusConnect()
	{
		EventBus::Connect(this);
	}

	template<typename Interface>
	inline void EventBus<Interface>::Handler::BusDisconnect()
	{
		EventBus::Disconnect(this);
	}
}

