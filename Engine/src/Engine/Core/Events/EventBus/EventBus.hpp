#pragma once
#include "pch.hpp"
#include "Engine/Core/Base.hpp"


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
		EventBus(const EventBus& other) = delete;
		EventBus& operator=(const EventBus& other) = delete;
		EventBus(EventBus&& other) = delete;
		EventBus& operator=(EventBus&& other) = delete;


		static bool HasHandlers();

		template<typename Function, typename... ArgsT>
		static void Broadcast(Function&& func, ArgsT&&... args);

		template<typename Function, typename... ArgsT>
		static void QueueBroadcast(Function&& func, ArgsT&& ...args);

		static void ExecuteQueue();
	private:
		EventBus() = default;
		~EventBus() = default;

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
		return !(EventBus::Get().m_Handlers.empty());
	}

	template<typename Interface>
	template<typename Function, typename ...ArgsT>
	inline void EventBus<Interface>::Broadcast(Function&& func, ArgsT&& ...args)
	{
		for (Handler* handler : EventBus::Get().m_Handlers) {
			(handler->*func)(std::forward<ArgsT>(args)...);
		}
	}

	template<typename Interface>
	template<typename Function, typename ...ArgsT>
	inline void EventBus<Interface>::QueueBroadcast(Function&& func, ArgsT&& ...args)
	{
		EventBus& instance = EventBus::Get();
		instance.m_Queue.push([func = std::forward<Function>(func) , ...args = std::forward<ArgsT>(args)](Handler* handler) mutable {
				(handler->*func)(std::forward<ArgsT>(args)...);
			}
		);
	}

	template<typename Interface>
	inline void EventBus<Interface>::ExecuteQueue()
	{
		while (!EventBus::Get().m_Queue.empty()) {
			Callback<Handler*> callback = EventBus::Get().m_Queue.front();
			for (Handler* handler : EventBus::Get().m_Handlers) {
				callback(handler);
			}
			EventBus::Get().m_Queue.pop();
		}
	}

	template<typename Interface>
	inline void EventBus<Interface>::Connect(Handler* handler)
	{
		auto pos = std::find(EventBus::Get().m_Handlers.begin(), EventBus::Get().m_Handlers.end(), handler);
		if (pos == EventBus::Get().m_Handlers.end()) {
			EventBus::Get().m_Handlers.push_back(handler);
		}
	}

	template<typename Interface>
	inline void EventBus<Interface>::Disconnect(Handler* handler)
	{
		auto pos = std::find(EventBus::Get().m_Handlers.begin(), EventBus::Get().m_Handlers.end(), handler);
		if (pos != EventBus::Get().m_Handlers.end()) {
			EventBus::Get().m_Handlers.erase(pos);
		}
		//TODO not tested
		if (!EventBus::HasHandlers()) {
			delete g_Instance;
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

