#include "olpch.h"

#include "NativeScriptSystem.h"
#include "Overlook/Scene/Entity.h"
#include "Overlook/Scene/Components.h"
#include "Overlook/Scene/ScriptableEntity.h"

namespace Overlook
{
	void NativeScriptSystem::OnUpdateRuntime(Timestep ts)
	{
		mScene->m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)  // nsc: native script component
			{
				// TODO: Move to Level::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, mScene };
					nsc.Instance->OnCreate();
				}

		nsc.Instance->OnUpdate(ts);
			});
	}
}