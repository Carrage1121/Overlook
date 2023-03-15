#pragma once

#include "Overlook/Renderer/EditorCamera.h"
#include "Overlook/Scene/Components.h"
#include "Overlook/Renderer/Texture.h"
#include "Overlook/Renderer/Framebuffer.h"

namespace Overlook
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();

		static void DrawModel(const glm::mat4& transform, const glm::vec3& cameraPos, ModelRendererComponent& ModelRendererComponent, int EntityID);

		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void EndScene();
	public:
		// shadow pass
		static Ref<class Framebuffer> lightFBO;
	};
}