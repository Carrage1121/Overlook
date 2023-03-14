#pragma once

#include "Overlook/Scene/System/System.h"
#include "Overlook/Scene/Scene.h"
#include "Overlook/Renderer/Buffer.h"

namespace Overlook
{
	struct EnvironmentHdrSettings
	{
		float SkyBoxLod = 0.0f;
		float exposure = 1.0f;
	};

	class EnvironmentSystem : public System
	{
	public:
		EnvironmentSystem(Scene* scene) : System(scene) {}
		virtual ~EnvironmentSystem() = default;
	public:
		void OnUpdateRuntime(Timestep ts) override;
		void OnUpdateEditor(Timestep ts, EditorCamera& camera) override;
	public:
		static EnvironmentHdrSettings environmentSettings;
	private:
		void DrawSkyBox(const glm::mat4& ViewMatrix, const glm::mat4& ProjectMatrix);
		void DrawEnvironmentHdr(const glm::mat4& ViewMatrix, const glm::mat4& ProjectMatrix);
	};
}
