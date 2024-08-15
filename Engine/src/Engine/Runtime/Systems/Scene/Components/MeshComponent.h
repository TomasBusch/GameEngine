#pragma once

namespace Engine::Components {

	struct MeshComponent {
		void* MeshData;

		MeshComponent() = default;
		MeshComponent(const MeshComponent&) = default;
		MeshComponent(void* data)
			:MeshData(data) {};

	};
}