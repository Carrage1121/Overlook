#pragma once
#include "Overlook/Core/Timestep.h"
#include "Overlook/Scene/System/System.h"

namespace Overlook
{
	class CSharpScriptSystem : public System
	{
	public:
		CSharpScriptSystem(Scene* scene) : System(scene) {}
		virtual ~CSharpScriptSystem() = default;
	public:
		void OnRuntimeStart() override;
		void OnRuntimeStop() override;
		void OnUpdateRuntime(Timestep ts) override;

	};
}

