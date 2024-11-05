#include "ModelManager.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Engine {
	Model ModelManager::loadModel(std::filesystem::path file_path)
	{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(file_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);


			ENGINE_CORE_ASSERT(!(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode), "ERROR::ASSIMP::")
			//if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			//	std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			//	return;
			//}

			processNode(scene->mRootNode, scene);
	}

	void processNode(aiNode* node, const aiScene* scene) {
		// process all the node's meshes (if any)
		for (uint32_t i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_Meshes.push_back(processMesh(mesh, scene));
		}
		// then do the same for each of its children
		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene);
		}
	}

	Mesh processMesh(aiMesh* mesh, const aiScene* scene) {
		std::vector<Vertex> vertices;
		std::vector<uint32_t> indices;
		Material* material = nullptr;

		float mat_index = 0.0f;

		if (mesh->mMaterialIndex >= 0) {
			aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
			aiString str;
			std::string albedo_path;
			std::string roughness_path;
			std::string metalness_path;
			std::string height_path;
			std::string normal_path;

			if (mat->GetTextureCount(aiTextureType_BASE_COLOR) > 0) {
				mat->GetTexture(aiTextureType_BASE_COLOR, 0, &str);
			}
			else {
				str.Set("res/missing_albedo.png");
			}
			albedo_path = str.C_Str();
			if (mat->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS) > 0) {
				mat->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &str);
			}
			else {
				str.Set("res/missing_roughness.png");
			}
			roughness_path = str.C_Str();
			if (mat->GetTextureCount(aiTextureType_METALNESS) > 0) {
				mat->GetTexture(aiTextureType_METALNESS, 0, &str);
			}
			else {
				str.Set("res/missing_metalness.png");
			}
			metalness_path = str.C_Str();
			if (mat->GetTextureCount(aiTextureType_HEIGHT) > 0) {
				mat->GetTexture(aiTextureType_HEIGHT, 0, &str);
			}
			else {
				str.Set("res/missing_height.png");
			}
			height_path = str.C_Str();
			if (mat->GetTextureCount(aiTextureType_NORMALS) > 0) {
				mat->GetTexture(aiTextureType_NORMALS, 0, &str);
			}
			else {
				str.Set("res/missing_normal.png");
			}
			normal_path = str.C_Str();

			material = new Material(albedo_path, roughness_path, metalness_path, height_path, normal_path);
			mat_index = mesh->mMaterialIndex;
		}

		for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
			Vertex vertex;

			glm::vec3 position;
			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;

			vertex.Position = position;

			glm::vec3 normals;
			normals.x = mesh->mNormals[i].x;
			normals.y = mesh->mNormals[i].y;
			normals.z = mesh->mNormals[i].z;

			vertex.Normal = normals;

			if (mesh->HasTextureCoords(0)) {
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.UV = vec;
			}
			else {
				vertex.UV = glm::vec2(0.0f, 0.0f);
			}

			if (mesh->HasVertexColors(0)) {
				vertex.Color.r = mesh->mColors[i]->r;
				vertex.Color.g = mesh->mColors[i]->g;
				vertex.Color.b = mesh->mColors[i]->b;
				vertex.Color.a = mesh->mColors[i]->a;
			}
			else {
				vertex.Color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
			}

			vertex.MaterialID = mat_index;

			vertices.push_back(vertex);
		}

		for (int i = 0; i < mesh->mNumFaces; i++) {
			aiFace face = mesh->mFaces[i];
			for (int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		return Mesh(vertices, indices, material);
	}

	Mesh Engine::ModelManager::loadMesh(std::filesystem::path file_path)
	{

		//return nullptr;
	}

	bool ModelManager::deleteMesh(Mesh* mesh)
	{

		return false;
	}

	bool ModelManager::releaseMesh(Mesh* mesh)
	{

		return false;
	}

	bool ModelManager::uploadMesh(Mesh* mesh)
	{

		return false;
	}
}