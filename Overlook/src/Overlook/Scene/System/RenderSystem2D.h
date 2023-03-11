#pragma once

#include "Overlook/Scene/System/System.h"
#include "Overlook/Scene/Scene.h"

namespace Overlook
{
	class RenderSystem2D : public System
	{
	public:
		RenderSystem2D(Scene* scene) : System(scene) {}
		virtual ~RenderSystem2D() = default;
	public:
		void OnUpdateRuntime(Timestep ts) override;
		void OnUpdateEditor(Timestep ts, EditorCamera& camera) override;
	};
}
