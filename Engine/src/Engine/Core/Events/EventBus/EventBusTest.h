#pragma once

#include "EventBus.h"
#include "Engine/Core/Events/Event.h"

struct GameEvent : public Engine::Event {
	int data;
};

struct IGameEvent {
	virtual void OnGameEvent(GameEvent e) = 0;
};

using GameEventBus = Engine::EventBus<IGameEvent>;

class GameEventHandler : public GameEventBus::Handler {
	public:
	GameEventHandler() {
		BusConnect();
	}
	~GameEventHandler() {
		BusDisconnect();
	}
	virtual void OnGameEvent(GameEvent e) override {
		std::cout << "GameEvent Recieved" << std::endl;
	}
};

class GameEventHandler2 : public GameEventBus::Handler {
public:
	virtual void OnGameEvent(GameEvent e) override {
		std::cout << "GameEvent Recieved 2" << std::endl;
	}
};

struct KeyEvent : public Engine::Event {
	int data;
};

struct IKeyEvent {
	virtual void OnKeyEvent(KeyEvent e) = 0;
};

using KeyEventBus = Engine::EventBus<IKeyEvent>;

class KeyEventHandler : public KeyEventBus::Handler {
public:
	KeyEventHandler() {
		BusConnect();
	}
	~KeyEventHandler() {
		BusDisconnect();
	}
	virtual void OnKeyEvent(KeyEvent e) override {
		std::cout << "KeyEvent Recieved" << std::endl;
	}
};

class KeyEventHandler2 : public KeyEventBus::Handler {
public:
	virtual void OnKeyEvent(KeyEvent e) override {
		std::cout << "KeyEvent Recieved 2" << std::endl;
	}
};