#pragma once
#include "entt.hpp"
#include "Overlook/Core/Timestep.h"
#include "Overlook/Core/UUID.h"
#include "Overlook/Renderer/EditorCamera.h"

namespace Overlook {
	class Entity;

	class Scene
	{
	public:
		Scene();
		~Scene();

		static Ref<Scene> Copy(Ref<Scene> other);

		Entity CreateEntity(const std::string& name = std::string());
		Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnRuntimeStart();
		void OnRuntimeStop();

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		void OnViewportResize(uint32_t width, uint32_t height);

		Entity GetEntityByUUID(UUID uuid);
		Entity GetPrimaryCameraEntity();

		entt::registry m_Registry;
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		std::unordered_map<UUID, entt::entity> m_EntityMap;

		std::vector<Scope<class System>> mSystems;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}