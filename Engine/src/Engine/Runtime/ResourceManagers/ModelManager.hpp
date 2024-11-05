#pragma once

#include "pch.hpp"

#include "Engine/Runtime/Renderer/Model.hpp"
#include "Engine/Runtime/Renderer/Mesh.hpp"
#include "Engine/RenderAPI/VertexBuffer.hpp"
#include "Engine/RenderAPI/IndexBuffer.hpp"

namespace Engine {
	class ModelManager {
	public:
		Model loadModel(std::filesystem::path file_path);

		//Loads mesh data to cpu memory
		Mesh loadMesh(std::filesystem::path file_path);
		
		//Removes mesh from manager and deletes mesh data from cpu.
		//Requires the mesh to be release first.
		bool  deleteMesh(Mesh* mesh);

		//Removes mesh data from gpu buffer.
		bool  releaseMesh(Mesh* mesh);

		//Loads mesh data to gpu buffers. May also delete mesh data from cpu memory.
		bool  uploadMesh(Mesh* mesh);

		struct MeshInfo {

			//Offset in vertex buffer to the begining of the mesh data (measured in number of vertices).
			uint32_t vertex_offset;
			//Number of vertices that belong to the mesh.
			uint32_t vertex_count;

			//Offset in index buffer to the begining of the mesh index data (measured in number of indices).
			uint32_t index_offset;
			//Number of indices that belong to the mesh.
			uint32_t index_count;
		};

	private:
		std::unordered_map<Mesh*, MeshInfo> m_Meshes;
		
		VertexBuffer* m_VertexBuffer;
		IndexBuffer* m_IndexBuffer;

	};
}