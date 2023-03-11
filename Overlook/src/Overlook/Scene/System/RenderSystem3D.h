#pragma once

#include "Overlook/Scene/System/System.h"
#include "Overlook/Scene/Scene.h"

namespace Overlook
{
	class RenderSystem3D : public System
	{
	public:
		RenderSystem3D(Scene* scene) : System(scene) {}
		virtual ~RenderSystem3D() = default;
	public:
		void OnUpdateRuntime(Timestep ts) override;
		void OnUpdateEditor(Timestep ts, EditorCamera& camera) override;
	};
}
