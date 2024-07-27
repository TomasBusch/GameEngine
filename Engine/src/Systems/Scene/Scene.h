#pragma once

//Based on Scene.h from The Cherno game engine series, adapted to decouple scenes and entities from other systems.

#include <entt/entity/registry.hpp>

namespace Engine {

	class Entity;

	class Scene {
	public:
		Scene();
		~Scene();

		Entity CreateEntity(const std::string& name = std::string());
		Entity DuplicateEntity(Entity entity);
		void DestroyEntity(Entity entity);

		Entity FindEntityByTag(std::string_view tag);

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);


	private:
		entt::registry m_Registry;


		friend class Entity;
	};
}