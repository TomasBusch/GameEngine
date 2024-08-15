#pragma once

#include "pch.h"

#include "Engine/Core/Base.h"

#include "Event.h"

namespace Engine {

    template<typename T>
    class EventQueue {
    public:
        EventQueue() = default;
        ~EventQueue() = default;

        void Push(T e) {
            m_EventQueue.push(e);
        }
        T Pop() {
            if (!m_EventQueue.empty()) {
                auto e = m_EventQueue.top();
                m_EventQueue.pop();
                return e;
            }
        }
        bool Empty() { return m_EventQueue.empty(); };
    private:       
        std::priority_queue<T, std::vector<T>, std::greater<T>> m_EventQueue;
    };
}