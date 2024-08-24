#pragma once

#include "Material.hpp"

namespace Engine {
	class Mesh {
	private:
		void* m_Data;
		Material* m_Material;
	};
}