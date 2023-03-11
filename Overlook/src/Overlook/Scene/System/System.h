#pragma once

#include "Overlook/Core/Timestep.h"
#include "Overlook/Scene/Scene.h"
#include "Overlook/Renderer/EditorCamera.h"

namespace Overlook
{
	class System
	{
	public:
		System() = delete;
		System(Scene* scene) : mScene(scene) {}
		virtual ~System() = default;
	public:
		virtual void OnUpdateEditor(Timestep ts, EditorCamera& camera) {}
		virtual void OnUpdateRuntime(Timestep ts) {}
		virtual void OnRuntiemStart() {}
		virtual void OnRuntimeStop() {}
	protected:
		Scene* mScene = nullptr;
	};
}