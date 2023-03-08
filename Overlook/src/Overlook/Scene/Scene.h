#pragma once
#include "entt.hpp"
#include "Overlook/Core/Timestep.h"
#include "Overlook/Renderer/EditorCamera.h"

namespace Overlook {
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();
		Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
		void OnUpdateEditor(Timestep ts, EditorCamera& camera);

		void OnUpdateRuntime3D(Timestep ts);
		void OnUpdateEditor3D(Timestep ts, EditorCamera& camera);
		void OnViewportResize(uint32_t width, uint32_t height);
		Entity GetPrimaryCameraEntity();
	private:
		template<typename T>
		void OnComponentAdded(Entity entity, T& component);

	private:
		entt::registry m_Registry;
		uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

		//std::vector<class System*> mSystems;
		friend class Entity;
		friend class SceneSerializer;
		friend class SceneHierarchyPanel;
	};
}