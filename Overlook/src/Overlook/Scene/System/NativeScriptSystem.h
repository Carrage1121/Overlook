#pragma once

#include "Overlook/Scene/System/System.h"
#include "Overlook/Scene/Scene.h"

namespace Overlook
{
	class NativeScriptSystem : public System
	{
	public:
		NativeScriptSystem(Scene* scene) : System(scene) {}
		virtual ~NativeScriptSystem() = default;
	public:
		void OnUpdateRuntime(Timestep ts) override;
	};
}