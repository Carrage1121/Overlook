#pragma once

#include "Overlook/Renderer/Texture.h"

#include "Overlook/Renderer/Camera.h"
#include "Overlook/Renderer/EditorCamera.h"
#include "Overlook/ModelLoader/PerspectiveCamera.h"
namespace Overlook
{
	class Renderer3D
	{
	public:
		static void Init();
		static void Shutdown();
	
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void BeginScene(const EditorCamera& camera);
		static void BeginScene(const PerspectiveCamera& camera); // TODO: Remove
		static void EndScene();
		static void Flush();
	
		static void ShowModel(const glm::mat4& transform, const glm::vec3& scale);
	
	private:
		static void FlushAndReset();
	};
}

