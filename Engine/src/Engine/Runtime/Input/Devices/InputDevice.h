#pragma once

namespace Engine::Input {

class InputDevice {
public:
	InputDevice(const std::string& id)
		:m_InputDeviceID(id)
	{};
private:
	std::string m_InputDeviceID;
};

}