#pragma once

#include "Overlook/Core/Base.h"
#include "Overlook/Core/Log.h"
#include "Overlook/Scene/Scene.h"
#include "Overlook/Scene/Entity.h"

#include "Overlook/Resource/IconManager/IconManager.h"
#include "Overlook/Resource/ConfigManager/ConfigManager.h"
#include "Overlook/Resource/ModeManager/ModeManager.h"

#include "Overlook/Scene/Components.h"

namespace Overlook {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender(bool* pOpen, bool* pOpenProperties);

		Entity GetSelectedEntity() const { return mSelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		template <typename componentType>
		void MenuAddComponent(const char* menuName, const char* menuItemName);
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> mContext;
		Entity mSelectionContext;
	};

}