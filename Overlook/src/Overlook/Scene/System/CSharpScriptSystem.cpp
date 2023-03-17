#include "olpch.h"
#include "CSharpScriptSystem.h"

#include "Overlook/Scripting/ScriptGlue.h"
#include "Overlook/Scripting/ScriptEngine.h"

namespace Overlook
{
	void CSharpScriptSystem::OnRuntimeStart()
	{
		ScriptEngine::OnRuntimeStart(this->mScene);
		// Instantiate all script entities

		auto view = mScene->m_Registry.view<ScriptComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this->mScene };
			ScriptEngine::OnCreateEntity(entity);
		}
	}

	void CSharpScriptSystem::OnUpdateRuntime(Timestep ts)
	{
		// C# Entity OnUpdate
		auto view = mScene->m_Registry.view<ScriptComponent>();
		for (auto e : view)
		{
			Entity entity = { e, this->mScene };
			ScriptEngine::OnUpdateEntity(entity, ts);
		}
	}

	void CSharpScriptSystem::OnRuntimeStop()
	{
		ScriptEngine::OnRuntimeStop();
	}
}