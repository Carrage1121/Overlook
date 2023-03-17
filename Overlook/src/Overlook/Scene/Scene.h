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

		Entity FindEntityByName(std::string_view name);
		Entity GetEntityByUUID(UUID uuid);
		Entity GetPrimaryCameraEntity();

		bool IsRunning() const { return m_IsRunning; }
		bool IsPaused() const { return m_IsPaused; }

		void SetPaused(bool paused) { m_IsPaused = paused; }

		void Step(int frames = 1);


		void DuplicateEntity(Entity entity);
		void ChangeDimMode();
		entt::registry m_Registry;
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
		bool m_IsRunning = false;
		bool m_IsPaused = false;
		int m_StepFrames = 0;

		std::unordered_map<UUID, entt::entity> m_EntityMap;

		std::vector<Scope<class System>> mSystems;

		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}