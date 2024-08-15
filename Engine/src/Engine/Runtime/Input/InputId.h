#pragma once

namespace Engine::Input {

	class InputId {
	public:
		InputId(const std::string& id)
			:m_InputId(id)
		{}
	private:
		std::string m_InputId;
	};

}